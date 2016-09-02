#include "texture.h"

#include "pkg.h"
#include "log.h"

TextureData gBackground;
TextureData gCharacter[2];
TextureData gEnemy[2];
TextureData gExit;
TextureData gPlatform;
TextureData gTitle;
TextureData gPressStart;

void loadTexture(char tPath[], pvr_ptr_t* tTexture, TextureSize* tTextureSize){
	tTextureSize->x = 0;
	tTextureSize->y = 0;
	loadTexturePKG(tPath, tTexture, &tTextureSize->x, &tTextureSize->y, PKG_NO_REALLOCATE_PVR_MEMORY);
}

void unloadTexture(TextureData tTexture){
	pvr_mem_free(tTexture.texture);	
}

void loadWorldTextures(){
	log("Load world textures");
	loadTexture("/rd/sprites/background.pkg", &gBackground.texture, &gBackground.textureSize);
	loadTexture("/rd/sprites/platform.pkg", &gPlatform.texture, &gPlatform.textureSize);
	loadTexture("/rd/sprites/exit.pkg", &gExit.texture, &gExit.textureSize);
}

void unloadWorldTextures(){
	log("Unload world textures");
	unloadTexture(gBackground);
	unloadTexture(gPlatform);
	unloadTexture(gExit);
}

void loadEnemyTextures(){
	log("Load character textures");
	loadTexture("/rd/sprites/enemy1.pkg", &gEnemy[0].texture, &gEnemy[0].textureSize);
	loadTexture("/rd/sprites/enemy2.pkg", &gEnemy[1].texture, &gEnemy[1].textureSize);
}

void unloadEnemyTextures(){
	log("Unload enemy textures");
	unloadTexture(gEnemy[0]);
	unloadTexture(gEnemy[1]);
}

void loadCharacterTextures(){
	log("Load character textures");
	loadTexture("/rd/sprites/char1.pkg", &gCharacter[0].texture, &gCharacter[0].textureSize);
	loadTexture("/rd/sprites/char2.pkg", &gCharacter[1].texture, &gCharacter[1].textureSize);
}

void unloadCharacterTextures(){
	log("Unload character textures");
	unloadTexture(gCharacter[0]);
	unloadTexture(gCharacter[1]);
}

void loadTitleTextures(){
	log("Load title textures");
	loadTexture("/rd/sprites/title.pkg", &gTitle.texture, &gTitle.textureSize);
	loadTexture("/rd/sprites/press_start.pkg", &gPressStart.texture, &gPressStart.textureSize);
}

void unloadTitleTextures(){
	log("Unoad title textures");
	unloadTexture(gTitle);
	unloadTexture(gPressStart);
}

void loadAllTextures(){
	loadWorldTextures();
	loadEnemyTextures();
	loadCharacterTextures();
	loadTitleTextures();
}

void unloadAllTextures(){
	unloadWorldTextures();
	unloadEnemyTextures();
	unloadCharacterTextures();
	unloadTitleTextures();
}

TextureData getBackgroundTexture(){
	return gBackground;
}

TextureData getCharacterTexture(int tFrame){
	return gCharacter[tFrame];
}

TextureData getEnemyTexture(int tFrame){
	return gEnemy[tFrame];
}

TextureData getExitTexture(){
	return gExit;
}

TextureData getPlatformTexture(){
	return gPlatform;
}

TextureData getTitleTexture(){
	return gTitle;
}

TextureData getPressStartTexture(){
	return gPressStart;
}

