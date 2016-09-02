#ifndef TARI_PKG_H
#define TARI_PKG_H

#include <kos.h>

#define PKG_REALLOCATE_PVR_MEMORY 1
#define PKG_NO_REALLOCATE_PVR_MEMORY 0

void loadTexturePKG(char tFileDir[], pvr_ptr_t* tTexture, int* tTextureSizeX, int* tTextureSizeY, char tMemoryReAllocationFlag);
void loadTextureKMG(char tFileDir[], pvr_ptr_t tTexture, int* tTextureSizeX, int* tTextureSizeY, char tMemoryReAllocationFlag);

#endif
