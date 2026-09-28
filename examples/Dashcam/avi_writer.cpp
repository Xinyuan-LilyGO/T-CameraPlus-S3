// =====================================================================
//  avi_writer.cpp  -  see avi_writer.h
// =====================================================================
#include "avi_writer.h"
#include <string.h>

// ---- little-endian buffer helpers -----------------------------------
static inline void put16(uint8_t *b, size_t &c, uint16_t v) {
    b[c++] = (uint8_t)(v & 0xFF);
    b[c++] = (uint8_t)((v >> 8) & 0xFF);
}
static inline void put32(uint8_t *b, size_t &c, uint32_t v) {
    b[c++] = (uint8_t)(v & 0xFF);
    b[c++] = (uint8_t)((v >> 8) & 0xFF);
    b[c++] = (uint8_t)((v >> 16) & 0xFF);
    b[c++] = (uint8_t)((v >> 24) & 0xFF);
}
static inline void put4cc(uint8_t *b, size_t &c, const char *s) {
    b[c++] = (uint8_t)s[0]; b[c++] = (uint8_t)s[1];
    b[c++] = (uint8_t)s[2]; b[c++] = (uint8_t)s[3];
}
static inline void wr32(uint8_t *p, uint32_t v) {
    p[0] = (uint8_t)(v); p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}

// Header byte sizes (RIFF .. 'movi' fourcc inclusive)
static const uint32_t HDR_LEN_NOAUDIO = 224;
static const uint32_t HDR_LEN_AUDIO   = 326;

bool AviWriter::begin(AviSink *sink, uint16_t width, uint16_t height,
                      bool hasAudio, uint32_t audioSampleRate,
                      uint16_t audioChannels, uint16_t audioBits,
                      uint8_t *indexMem, size_t indexMemBytes)
{
    if (!sink || !indexMem || indexMemBytes < 16) return false;

    _sink       = sink;
    _w          = width;
    _h          = height;
    _hasAudio   = hasAudio;
    _audioRate  = audioSampleRate ? audioSampleRate : 16000;
    _audioCh    = audioChannels ? audioChannels : 1;
    _audioBits  = audioBits ? audioBits : 16;
    _blockAlign = (uint16_t)(_audioCh * (_audioBits / 8));
    if (_blockAlign == 0) _blockAlign = 2;

    _index      = indexMem;
    _indexCap   = indexMemBytes / 16;
    _indexCount = 0;

    _headerLen      = _hasAudio ? HDR_LEN_AUDIO : HDR_LEN_NOAUDIO;
    _moviDataStart  = _headerLen - 4;     // file offset of the 'movi' FOURCC
    _moviChunkBytes = 0;
    _videoFrames    = 0;
    _audioBytes     = 0;
    _maxChunk       = 0;
    _written        = 0;

    // Write a placeholder header (counts patched in end()).
    uint8_t hdr[HDR_LEN_AUDIO];
    if (!buildHeader(hdr, 0, 15.0f)) return false;
    if (!_sink->seek(0)) return false;
    if (_sink->write(hdr, _headerLen) != _headerLen) return false;
    _written = _headerLen;

    _ok = true;
    return true;
}

bool AviWriter::buildHeader(uint8_t *b, uint32_t moviChunksBytes, float fps)
{
    if (fps < 1.0f) fps = 1.0f;
    const uint32_t usPerFrame = (uint32_t)(1000000.0f / fps + 0.5f);
    const uint32_t vidRate    = (uint32_t)(fps + 0.5f);
    const uint32_t idxBytes   = 8 + (uint32_t)_indexCount * 16;
    const uint32_t fileSize   = _headerLen + moviChunksBytes + idxBytes;

    // hdrl LIST content size
    const uint32_t hdrlContent = 192u + (_hasAudio ? 102u : 0u);

    uint32_t bytesPerSec = 0;
    if (fps > 0.0f && _videoFrames > 0) {
        float elapsed = (float)_videoFrames / fps;
        if (elapsed > 0.01f) bytesPerSec = (uint32_t)((double)moviChunksBytes / elapsed);
    }

    size_t c = 0;

    // ---- RIFF ----
    put4cc(b, c, "RIFF");
    put32 (b, c, fileSize - 8);
    put4cc(b, c, "AVI ");

    // ---- LIST 'hdrl' ----
    put4cc(b, c, "LIST");
    put32 (b, c, hdrlContent);
    put4cc(b, c, "hdrl");

    //   avih (MainAVIHeader, 56 bytes)
    put4cc(b, c, "avih");
    put32 (b, c, 56);
    put32 (b, c, usPerFrame);                 // dwMicroSecPerFrame
    put32 (b, c, bytesPerSec);                // dwMaxBytesPerSec
    put32 (b, c, 0);                          // dwPaddingGranularity
    put32 (b, c, 0x10 | (_hasAudio ? 0x100 : 0)); // AVIF_HASINDEX | ISINTERLEAVED
    put32 (b, c, _videoFrames);               // dwTotalFrames
    put32 (b, c, 0);                          // dwInitialFrames
    put32 (b, c, _hasAudio ? 2 : 1);          // dwStreams
    put32 (b, c, _maxChunk);                  // dwSuggestedBufferSize
    put32 (b, c, _w);                         // dwWidth
    put32 (b, c, _h);                         // dwHeight
    put32 (b, c, 0); put32(b, c, 0);          // dwReserved[0..1]
    put32 (b, c, 0); put32(b, c, 0);          // dwReserved[2..3]

    //   LIST 'strl' (video)
    put4cc(b, c, "LIST");
    put32 (b, c, 116);
    put4cc(b, c, "strl");
    //     strh (video stream header, 56 bytes)
    put4cc(b, c, "strh");
    put32 (b, c, 56);
    put4cc(b, c, "vids");
    put4cc(b, c, "MJPG");                     // fccHandler
    put32 (b, c, 0);                          // dwFlags
    put16 (b, c, 0);                          // wPriority
    put16 (b, c, 0);                          // wLanguage
    put32 (b, c, 0);                          // dwInitialFrames
    put32 (b, c, 1);                          // dwScale
    put32 (b, c, vidRate);                    // dwRate -> fps
    put32 (b, c, 0);                          // dwStart
    put32 (b, c, _videoFrames);               // dwLength (frames)
    put32 (b, c, _maxChunk);                  // dwSuggestedBufferSize
    put32 (b, c, 0xFFFFFFFFu);                // dwQuality
    put32 (b, c, 0);                          // dwSampleSize
    put16 (b, c, 0); put16(b, c, 0);          // rcFrame left, top
    put16 (b, c, _w); put16(b, c, _h);        // rcFrame right, bottom
    //     strf (BITMAPINFOHEADER, 40 bytes)
    put4cc(b, c, "strf");
    put32 (b, c, 40);
    put32 (b, c, 40);                         // biSize
    put32 (b, c, _w);                         // biWidth
    put32 (b, c, _h);                         // biHeight
    put16 (b, c, 1);                          // biPlanes
    put16 (b, c, 24);                         // biBitCount
    put4cc(b, c, "MJPG");                     // biCompression
    put32 (b, c, (uint32_t)_w * _h * 3);      // biSizeImage
    put32 (b, c, 0); put32(b, c, 0);          // biX/YPelsPerMeter
    put32 (b, c, 0); put32(b, c, 0);          // biClrUsed / biClrImportant

    if (_hasAudio) {
        const uint32_t avgBytesPerSec = _audioRate * _blockAlign;
        const uint32_t sampleFrames   = _audioBytes / (_blockAlign ? _blockAlign : 1);
        //   LIST 'strl' (audio)
        put4cc(b, c, "LIST");
        put32 (b, c, 94);
        put4cc(b, c, "strl");
        //     strh (audio stream header, 56 bytes)
        put4cc(b, c, "strh");
        put32 (b, c, 56);
        put4cc(b, c, "auds");
        put32 (b, c, 1);                      // fccHandler (PCM)
        put32 (b, c, 0);                      // dwFlags
        put16 (b, c, 0);                      // wPriority
        put16 (b, c, 0);                      // wLanguage
        put32 (b, c, 0);                      // dwInitialFrames
        put32 (b, c, 1);                      // dwScale
        put32 (b, c, _audioRate);             // dwRate
        put32 (b, c, 0);                      // dwStart
        put32 (b, c, sampleFrames);           // dwLength (sample frames)
        put32 (b, c, avgBytesPerSec);         // dwSuggestedBufferSize
        put32 (b, c, 0xFFFFFFFFu);            // dwQuality
        put32 (b, c, _blockAlign);            // dwSampleSize
        put16 (b, c, 0); put16(b, c, 0);      // rcFrame
        put16 (b, c, 0); put16(b, c, 0);
        //     strf (WAVEFORMATEX, 18 bytes)
        put4cc(b, c, "strf");
        put32 (b, c, 18);
        put16 (b, c, 1);                      // wFormatTag = PCM
        put16 (b, c, _audioCh);               // nChannels
        put32 (b, c, _audioRate);             // nSamplesPerSec
        put32 (b, c, avgBytesPerSec);         // nAvgBytesPerSec
        put16 (b, c, _blockAlign);            // nBlockAlign
        put16 (b, c, _audioBits);             // wBitsPerSample
        put16 (b, c, 0);                      // cbSize
    }

    // ---- LIST 'movi' ----
    put4cc(b, c, "LIST");
    put32 (b, c, moviChunksBytes + 4);        // size covers 'movi' + chunks
    put4cc(b, c, "movi");

    return c == _headerLen;
}

bool AviWriter::writeChunk(const char ckid[4], const uint8_t *data,
                           uint32_t len, uint32_t flags)
{
    if (!_ok) return false;
    if (_indexCount >= _indexCap) return false;

    const uint32_t chunkPos = _sink->pos();
    uint8_t hdr[8];
    size_t  hc = 0;
    put4cc(hdr, hc, ckid);
    put32 (hdr, hc, len);
    if (_sink->write(hdr, 8) != 8) return false;
    if (len && _sink->write(data, len) != len) return false;

    uint32_t pad = (len & 1u);                // RIFF chunks are word-aligned
    if (pad) {
        uint8_t z = 0;
        if (_sink->write(&z, 1) != 1) return false;
    }

    // index entry (stored in final little-endian on-disk layout)
    uint8_t *e = _index + _indexCount * 16;
    e[0] = (uint8_t)ckid[0]; e[1] = (uint8_t)ckid[1];
    e[2] = (uint8_t)ckid[2]; e[3] = (uint8_t)ckid[3];
    wr32(e + 4, flags);
    wr32(e + 8, chunkPos - _moviDataStart);   // offset relative to 'movi' fourcc
    wr32(e + 12, len);
    _indexCount++;

    _moviChunkBytes += 8 + len + pad;
    _written        += 8 + len + pad;
    if (len > _maxChunk) _maxChunk = len;
    return true;
}

bool AviWriter::addVideoFrame(const uint8_t *jpeg, uint32_t len)
{
    if (!writeChunk("00dc", jpeg, len, 0x10 /*AVIIF_KEYFRAME*/)) return false;
    _videoFrames++;
    return true;
}

bool AviWriter::addAudioChunk(const uint8_t *pcm, uint32_t len)
{
    if (!_hasAudio || len == 0) return true;
    if (!writeChunk("01wb", pcm, len, 0)) return false;
    _audioBytes += len;
    return true;
}

bool AviWriter::end(float measuredFps)
{
    if (!_ok) return false;

    // 1) rewrite the header with final counts / timing
    uint8_t hdr[HDR_LEN_AUDIO];
    if (!buildHeader(hdr, _moviChunkBytes, measuredFps)) return false;
    if (!_sink->seek(0)) return false;
    if (_sink->write(hdr, _headerLen) != _headerLen) return false;

    // 2) append idx1 right after the movi chunks
    const uint32_t idxPos = _headerLen + _moviChunkBytes;
    if (!_sink->seek(idxPos)) return false;
    uint8_t ih[8];
    size_t  c = 0;
    put4cc(ih, c, "idx1");
    put32 (ih, c, (uint32_t)_indexCount * 16);
    if (_sink->write(ih, 8) != 8) return false;
    if (_indexCount &&
        _sink->write(_index, _indexCount * 16) != _indexCount * 16) return false;

    _sink->flush();
    _ok = false;     // clip closed
    return true;
}
