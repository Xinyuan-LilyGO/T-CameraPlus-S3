// =====================================================================
//  test_avi.cpp  -  host-side sanity test for the AVI muxer
//
//  Build & run:
//    g++ -std=c++14 -I../../src test_avi.cpp ../../src/avi_writer.cpp -o test_avi
//    ./test_avi
//
//  Verifies that AviWriter produces a self-consistent RIFF/AVI:
//   - RIFF/AVI/LIST/movi/idx1 structure & sizes
//   - every idx1 entry points at a real chunk with matching id + length
//   - header counters (frames, streams) match what we wrote
// =====================================================================
#include "avi_writer.h"
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>

// ---- in-memory sink --------------------------------------------------
struct MemSink : public AviSink {
    std::vector<uint8_t> buf;
    uint32_t cur = 0;
    size_t write(const void *data, size_t len) override {
        if (cur + len > buf.size()) buf.resize(cur + len);
        memcpy(buf.data() + cur, data, len);
        cur += (uint32_t)len;
        return len;
    }
    bool seek(uint32_t p) override { cur = p; if (p > buf.size()) buf.resize(p); return true; }
    uint32_t pos() override { return cur; }
};

static uint32_t rd32(const uint8_t *p) {
    return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24);
}
static bool fcc(const uint8_t *p, const char *s) { return memcmp(p, s, 4) == 0; }

static int failures = 0;
#define CHECK(cond, msg) do { if (!(cond)) { printf("  FAIL: %s\n", msg); failures++; } \
                              else { printf("  ok  : %s\n", msg); } } while (0)

int main() {
    printf("AVI muxer host test\n-------------------\n");

    MemSink sink;
    AviWriter avi;

    const uint16_t W = 800, H = 600;
    const uint32_t RATE = 16000;
    static uint8_t idxMem[6000 * 16];

    bool ok = avi.begin(&sink, W, H, /*audio*/ true, RATE, 1, 16,
                        idxMem, sizeof(idxMem));
    CHECK(ok, "begin() succeeds");

    // Fake content: 30 JPEG frames of varying (odd & even) sizes + audio.
    const int NFRAMES = 30;
    std::vector<uint8_t> jpg, pcm;
    uint32_t totalAudio = 0;
    for (int i = 0; i < NFRAMES; ++i) {
        uint32_t jl = 1000 + (i * 37) % 533;          // mix of odd/even lengths
        jpg.assign(jl, (uint8_t)(0xD8 + i));
        jpg[0] = 0xFF; jpg[1] = 0xD8;                  // pretend SOI
        CHECK(avi.addVideoFrame(jpg.data(), jl), "addVideoFrame");
        uint32_t al = 512;                              // 256 samples * 2 bytes
        pcm.assign(al, (uint8_t)i);
        CHECK(avi.addAudioChunk(pcm.data(), al), "addAudioChunk");
        totalAudio += al;
    }
    CHECK(avi.videoFrames() == (uint32_t)NFRAMES, "video frame count");

    ok = avi.end(15.0f);
    CHECK(ok, "end() succeeds");

    // ---------- parse & validate ----------
    const uint8_t *b = sink.buf.data();
    const uint32_t n = (uint32_t)sink.buf.size();
    printf("  file size = %u bytes\n", n);

    CHECK(fcc(b, "RIFF"), "starts with RIFF");
    CHECK(fcc(b + 8, "AVI "), "form type AVI");
    CHECK(rd32(b + 4) == n - 8, "RIFF size == filesize-8");

    CHECK(fcc(b + 12, "LIST") && fcc(b + 20, "hdrl"), "hdrl LIST present");
    uint32_t hdrlSize = rd32(b + 16);
    // movi LIST sits right after the hdrl LIST (12 + 8 + hdrlSize)
    uint32_t moviListPos = 12 + 8 + hdrlSize;
    CHECK(fcc(b + moviListPos, "LIST"), "movi LIST tag where expected");
    CHECK(fcc(b + moviListPos + 8, "movi"), "movi fourcc present");
    uint32_t moviSize = rd32(b + moviListPos + 4);
    uint32_t moviDataStart = moviListPos + 8;          // 'movi' fourcc offset

    // avih: total frames + streams
    // avih data begins after: RIFF(12)+LIST/hdrl(12)+'avih'(4)+size(4)=32
    const uint8_t *avih = b + 32;
    CHECK(rd32(avih + 16) == (uint32_t)NFRAMES, "avih dwTotalFrames");
    CHECK(rd32(avih + 24) == 2, "avih dwStreams == 2 (video+audio)");

    // Walk the movi chunks and tally.
    uint32_t p = moviDataStart + 4;                    // first chunk
    uint32_t moviEnd = moviDataStart + moviSize;       // exclusive
    int vid = 0, aud = 0;
    while (p + 8 <= moviEnd) {
        const uint8_t *ck = b + p;
        uint32_t len = rd32(ck + 4);
        if (fcc(ck, "00dc")) vid++;
        else if (fcc(ck, "01wb")) aud++;
        p += 8 + len + (len & 1);
    }
    CHECK(vid == NFRAMES, "movi contains all video chunks");
    CHECK(aud == NFRAMES, "movi contains all audio chunks");
    CHECK(p == moviEnd, "movi chunk walk lands exactly on movi end");

    // idx1 must follow the movi LIST.
    uint32_t idxPos = moviListPos + 8 + moviSize;
    CHECK(idxPos + 8 <= n, "idx1 within file");
    CHECK(fcc(b + idxPos, "idx1"), "idx1 tag present");
    uint32_t idxSize = rd32(b + idxPos + 4);
    CHECK(idxSize == (uint32_t)(vid + aud) * 16, "idx1 size matches chunk count");
    CHECK(idxPos + 8 + idxSize == n, "idx1 is the last structure in the file");

    // Validate each index entry points at the right chunk.
    int badEntries = 0;
    uint32_t entries = idxSize / 16;
    for (uint32_t i = 0; i < entries; ++i) {
        const uint8_t *e = b + idxPos + 8 + i * 16;
        uint32_t off = rd32(e + 8);                    // relative to moviDataStart
        uint32_t len = rd32(e + 12);
        const uint8_t *ck = b + moviDataStart + off;
        if (memcmp(e, ck, 4) != 0) badEntries++;        // ckid must match
        else if (rd32(ck + 4) != len) badEntries++;     // length must match
    }
    CHECK(badEntries == 0, "every idx1 entry resolves to its chunk");

    printf("-------------------\n%s (%d failure%s)\n",
           failures ? "FAILED" : "PASSED", failures, failures == 1 ? "" : "s");
    return failures ? 1 : 0;
}
