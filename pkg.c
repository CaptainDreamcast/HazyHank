#include "pkg.h"

#include <kos.h>
#include "quicklz.h"
#include <kos/string.h>

#include "file.h"
#include "log.h"



#define HEADER_SIZE_KMG 64
// TODO: use kmg.h from KOS

void loadTexturePKG(char tFileDir[], pvr_ptr_t* tTexture, int* tTextureSizeX, int* tTextureSizeY, char tMemoryReAllocationFlag){

	qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
	size_t bufferLength;
	file_t pkgFile;
	char* mipMapData;
	char* kmgData;

	pkgFile = fileOpen(tFileDir, O_RDONLY);

	if(pkgFile == FILEHND_INVALID) {
		logError("Couldn't open file: Try returning to menu...");
		logErrorString(tFileDir);
		arch_menu();
	}

	bufferLength = fileTotal(pkgFile);
	debugInteger(bufferLength);

	mipMapData = fileMemoryMap(pkgFile);

	bufferLength = qlz_size_decompressed(mipMapData);
	debugInteger(bufferLength);

	kmgData = (char*) malloc(bufferLength);

	// decompress and write result
	bufferLength = qlz_decompress(mipMapData, kmgData, state_decompress);
	debugInteger(bufferLength);

	fileClose(pkgFile);
	free(state_decompress);

	(*tTextureSizeX) = 0;
	(*tTextureSizeY) = 0;

	memcpy4(tTextureSizeX, kmgData+16, sizeof(*tTextureSizeX));
	memcpy4(tTextureSizeY, kmgData+20, sizeof(*tTextureSizeY));

	if(tMemoryReAllocationFlag == PKG_REALLOCATE_PVR_MEMORY){
		pvr_mem_free(*tTexture);
		(*tTexture) = pvr_mem_malloc(bufferLength-HEADER_SIZE_KMG);
	}
	else if(tMemoryReAllocationFlag == PKG_NO_REALLOCATE_PVR_MEMORY) {
		(*tTexture) = pvr_mem_malloc(bufferLength-HEADER_SIZE_KMG);
	}

	sq_cpy((*tTexture), kmgData+HEADER_SIZE_KMG, bufferLength-HEADER_SIZE_KMG);

	free(kmgData);
}


void loadTextureKMG(char tFileDir[], pvr_ptr_t tTexture, int* tTextureSizeX, int* tTextureSizeY, char tMemoryReAllocationFlag){
	size_t bufferLength;
	file_t kmgFile;
	char* kmgData;

	kmgFile = fileOpen(tFileDir, O_RDONLY);

	if(kmgFile == FILEHND_INVALID) {
		printf("\nCouldn't open: (%s)\nAborting Kernel any minute now...\n", tFileDir);
	}

	bufferLength = fileTotal(kmgFile);

	kmgData = fileMemoryMap(kmgFile);

	memcpy4(tTextureSizeX, kmgData+16, sizeof(*tTextureSizeX));
	memcpy4(tTextureSizeY, kmgData+20, sizeof(*tTextureSizeY));

	if(tMemoryReAllocationFlag == PKG_REALLOCATE_PVR_MEMORY){
	pvr_mem_free(tTexture);
	tTexture = NULL;
	tTexture = pvr_mem_malloc(bufferLength-HEADER_SIZE_KMG);
	}

	//memcpy4(TextureUsed, KMGData+HeaderSizeKMG, BufferLength-HeaderSizeKMG);
	sq_cpy(tTexture, kmgData+HEADER_SIZE_KMG, bufferLength-HEADER_SIZE_KMG);


	fileClose(kmgFile);
}
