// =====================================================================
//  avi_writer.h  -  Streaming Motion-JPEG (+ optional PCM audio) AVI muxer
//
//  Pure C++ (no Arduino headers) so it can be unit-tested on a host PC.
//  Writes a standard RIFF/AVI container with an idx1 index, suitable for
//  playback in VLC / ffmpeg / most players.
//
//  Usage:
//      FileSink sink(file);                 // your AviSink implementation
//      AviWriter avi;
//      avi.begin(&sink, w, h, true, 16000, 1, 16, idxMem, idxBytes);
//      avi.addVideoFrame(jpeg, len);        // once per camera frame
//      avi.addAudioChunk(pcm, len);         // periodically (16-bit PCM)
//      avi.end(measuredFps);                // finalize header + idx1
// =====================================================================
#pragma once
#include <stdint.h>
#include <stddef.h>

// Abstract output sink. On the device this wraps an SD `File`; on the host
// it wraps an std::fstream (see test/host/test_avi.cpp).
struct AviSink {
    virtual ~AviSink() {}
    virtual size_t   write(const void *data, size_t len) = 0;
    virtual bool     seek(uint32_t pos)                  = 0;
    virtual uint32_t pos()                               = 0;
    virtual void     flush()                             {}
};

class AviWriter {
public:
    AviWriter() = default;

    // indexMem must stay valid for the lifetime of the clip; size in bytes.
    // Each index entry uses 16 bytes -> capacity = indexMemBytes / 16.
    bool begin(AviSink *sink, uint16_t width, uint16_t height,
               bool hasAudio, uint32_t audioSampleRate,
               uint16_t audioChannels, uint16_t audioBits,
               uint8_t *indexMem, size_t indexMemBytes);

    // Append one compressed JPEG frame ("00dc"). Returns false on I/O error
    // or when the index is full (caller should rotate the clip).
    bool addVideoFrame(const uint8_t *jpeg, uint32_t len);

    // Append one PCM audio chunk ("01wb"). No-op if begun without audio.
    bool addAudioChunk(const uint8_t *pcm, uint32_t len);

    // Rewrite the header with final counts/fps and append idx1. measuredFps
    // should be videoFrames / elapsedSeconds (used for the timing fields).
    bool end(float measuredFps);

    uint32_t videoFrames()  const { return _videoFrames; }
    uint32_t audioBytes()   const { return _audioBytes; }
    uint64_t bytesWritten() const { return _written; }
    bool     indexFull()    const { return _indexCount >= _indexCap; }

private:
    bool buildHeader(uint8_t *buf, uint32_t moviChunksBytes, float fps);
    bool writeChunk(const char ckid[4], const uint8_t *data, uint32_t len,
                    uint32_t flags);

    AviSink *_sink = nullptr;
    uint16_t _w = 0, _h = 0;
    bool     _hasAudio = false;
    uint32_t _audioRate = 16000;
    uint16_t _audioCh = 1, _audioBits = 16;
    uint16_t _blockAlign = 2;          // audioCh * audioBits/8

    uint8_t *_index = nullptr;         // 16 bytes/entry: ckid,flags,offset,len
    size_t   _indexCap = 0;
    size_t   _indexCount = 0;

    uint32_t _headerLen = 0;           // bytes from RIFF up to & incl 'movi'
    uint32_t _moviDataStart = 0;       // file offset of the 'movi' FOURCC
    uint32_t _moviChunkBytes = 0;      // running sum of chunk hdr+data+pad
    uint32_t _videoFrames = 0;
    uint32_t _audioBytes = 0;
    uint32_t _maxChunk = 0;            // largest single chunk payload
    uint64_t _written = 0;
    bool     _ok = false;
};
