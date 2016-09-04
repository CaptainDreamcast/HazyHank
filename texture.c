#include "texture.h"

#include <tari/log.h>

TextureData gBackground;
TextureData gCharacter[2];
TextureData gEnemy[2];
TextureData gExit;
TextureData gPlatform;
TextureData gTitle;
TextureData gPressStart;

void loadWorldTextures() {
  log("Load world textures");
  gBackground = loadTexturePKG("/rd/sprites/background.pkg");
  gPlatform = loadTexturePKG("/rd/sprites/platform.pkg");
  gExit = loadTexturePKG("/rd/sprites/exit.pkg");
}

void unloadWorldTextures() {
  log("Unload world textures");
  unloadTexture(gBackground);
  unloadTexture(gPlatform);
  unloadTexture(gExit);
}

void loadEnemyTextures() {
  log("Load character textures");
  gEnemy[0] = loadTexturePKG("/rd/sprites/enemy1.pkg");
  gEnemy[1] = loadTexturePKG("/rd/sprites/enemy2.pkg");
}

void unloadEnemyTextures() {
  log("Unload enemy textures");
  unloadTexture(gEnemy[0]);
  unloadTexture(gEnemy[1]);
}

void loadCharacterTextures() {
  log("Load character textures");
  gCharacter[0] = loadTexturePKG("/rd/sprites/char1.pkg");
  gCharacter[1] = loadTexturePKG("/rd/sprites/char2.pkg");
}

void unloadCharacterTextures() {
  log("Unload character textures");
  unloadTexture(gCharacter[0]);
  unloadTexture(gCharacter[1]);
}

void loadTitleTextures() {
  log("Load title textures");
  gTitle = loadTexturePKG("/rd/sprites/title.pkg");
  gPressStart = loadTexturePKG("/rd/sprites/press_start.pkg");
}

void unloadTitleTextures() {
  log("Unoad title textures");
  unloadTexture(gTitle);
  unloadTexture(gPressStart);
}

void loadAllTextures() {
  loadWorldTextures();
  loadEnemyTextures();
  loadCharacterTextures();
  loadTitleTextures();
}

void unloadAllTextures() {
  unloadWorldTextures();
  unloadEnemyTextures();
  unloadCharacterTextures();
  unloadTitleTextures();
}

TextureData getBackgroundTexture() {
  return gBackground;
}

TextureData getCharacterTexture(int tFrame) {
  return gCharacter[tFrame];
}

TextureData getEnemyTexture(int tFrame) {
  return gEnemy[tFrame];
}

TextureData getExitTexture() {
  return gExit;
}

TextureData getPlatformTexture() {
  return gPlatform;
}

TextureData getTitleTexture() {
  return gTitle;
}

TextureData getPressStartTexture() {
  return gPressStart;
}
