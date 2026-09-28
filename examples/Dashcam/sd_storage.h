// =====================================================================
//  sd_storage.h  -  microSD card: mount, clip naming, loop-delete
//
//  NOTE: every function here touches the shared SPI bus. The CALLER must
//  hold spibus::lock() (or use spibus::Guard) around these calls, except
//  begin() which is called once during setup before any tasks run.
// =====================================================================
#pragma once
#include <stdint.h>
#include <FS.h>

namespace storage {

bool     begin();                       // mount card + create folders
bool     mounted();

uint64_t totalBytes();
uint64_t freeBytes();
uint32_t freeMB();

// Build the next sequential file paths (counter persisted in NVS).
void nextClipPath(char *out, size_t outLen);
void nextPhotoPath(char *out, size_t outLen);

// Delete oldest clips until at least minFreeMB is available.
// Returns true if the card now has enough space.
bool ensureFreeSpace(uint32_t minFreeMB);

}  // namespace storage
