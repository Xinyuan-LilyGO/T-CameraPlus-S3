// =====================================================================
//  recorder.h  -  dashcam recording engine
//
//  Ties together camera + mic + AVI muxer + SD storage:
//   - continuous loop recording into REC_SEGMENT_SECONDS clips
//   - auto-deletes oldest clips when the card gets full
//   - hands the latest JPEG to the UI task for live preview
//   - on-demand still-photo snapshots
//
//  captureLoopOnce() runs on the recorder task; getPreview()/stats run on
//  the UI task. State shared across the two is mutex / atomically guarded.
// =====================================================================
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace recorder {

bool begin();                 // allocate buffers
void start();                 // open first clip + start recording
void stop();                  // finalize current clip
void toggle();
bool isRecording();

void requestSnapshot();       // capture a still on the next frame

void captureLoopOnce();       // <- call repeatedly from the recorder task

// UI helpers (read-only views of recorder state)
bool        getPreview(uint8_t *dst, size_t cap, size_t *outLen);
uint32_t    elapsedSec();
float       fps();
uint32_t    cachedFreeMB();
const char *lastError();

}  // namespace recorder
