#ifndef TEXTURE_H
#define TEXTURE_H

#include "worlddata.h"
#include "characterdata.h"
#include "basetypes.h"


typedef struct{
	pvr_ptr_t texture;
	TextureSize textureSize;
} TextureData;

typedef struct { // TODO: refactor completely from Dolmexica
	float filePositionX1;
	float filePositionY1;
	float filePositionX2;
	float filePositionY2;
} FontCharacterData;

void loadAllTextures();
void unloadAllTextures();
 
TextureData getTitleTexture();
TextureData getPressStartTexture();
TextureData getBackgroundTexture();
TextureData getCharacterTexture(int tFrame);
TextureData getEnemyTexture(int tFrame);
TextureData getExitTexture();
TextureData getPlatformTexture();
TextureData getFontTexture();
FontCharacterData getFontCharacterData(char tChar);

void setFont(char tFileDirHeader[], char tFileDirTexture[]);

#endif
