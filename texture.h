#ifndef TEXTURE_H
#define TEXTURE_H

#include <tari/texture.h>

#include "worlddata.h"
#include "characterdata.h"
#include "basetypes.h"

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
