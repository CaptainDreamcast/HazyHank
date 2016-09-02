#ifndef TEXTURE_H
#define TEXTURE_H

#include "worlddata.h"
#include "characterdata.h"
#include "basetypes.h"


typedef struct{
	pvr_ptr_t texture;
	TextureSize textureSize;
} TextureData;

void loadAllTextures();
void unloadAllTextures();
 
TextureData getTitleTexture();
TextureData getPressStartTexture();
TextureData getBackgroundTexture();
TextureData getCharacterTexture(int tFrame);
TextureData getEnemyTexture(int tFrame);
TextureData getExitTexture();
TextureData getPlatformTexture();


#endif
