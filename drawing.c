#include "drawing.h"

#include <stdlib.h>

#include <kos.h>
#include <dc/matrix3d.h>
#include <tari/log.h>
#include <tari/drawing.h>

#include "texture.h"

#define M_PI 3.14159

double inverseScreenY(double y) {
  return (SCREEN_SIZE_Y - y);
}

double getDrawY(double y, Rectangle tTexturePosition) {
  double sizeY = tTexturePosition.bottomRight.y - tTexturePosition.topLeft.y;

  return inverseScreenY(y + sizeY);
}

void updateTiltingMatrix(double tTiltAngle) {
  float dx1 = MIDDLE_OF_SCREEN_X;
  float dy1 = MIDDLE_OF_SCREEN_Y;
  float dz1 = 0;

  float dx2 = -MIDDLE_OF_SCREEN_X;
  float dy2 = -MIDDLE_OF_SCREEN_Y;
  float dz2 = 0;

  mat_identity();
  mat_translate(dx1, dy1, dz1);
  mat_rotate_z(tTiltAngle);
  mat_translate(dx2, dy2, dz2);
}

void drawCharacter(WorldData* tWorldData, CharacterData* tCharacterData) {
  debugLog("Draw character");
  TextureData textureData = getCharacterTexture(tCharacterData->animation.mFrame);
  FaceDirection faceDirection = tCharacterData->faceDirection;

  Rectangle tTexturePosition;
  tTexturePosition.topLeft.x = (faceDirection == FACE_RIGHT) ? 0 : (textureData.mTextureSize.x - 1);
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = (faceDirection != FACE_RIGHT) ? 0 : (textureData.mTextureSize.x - 1);
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  Position drawPos = tCharacterData->physics.mPosition;
  drawPos.y = getDrawY(drawPos.y, tTexturePosition);

  drawSprite(textureData, drawPos, tTexturePosition);
}

void drawEnemies(WorldData* tWorldData) {
  debugLog("Draw enemies");

  int i;
  for (i = 0; i < tWorldData->enemyAmount; i++) {
    FaceDirection faceDirection = tWorldData->enemies[i].faceDirection;
    TextureData textureData = getEnemyTexture(tWorldData->enemies[i].animation.mFrame);

    Rectangle tTexturePosition;
    tTexturePosition.topLeft.x = (faceDirection == FACE_RIGHT) ? 0 : (textureData.mTextureSize.x - 1);
    tTexturePosition.topLeft.y = 0;
    tTexturePosition.bottomRight.x = (faceDirection != FACE_RIGHT) ? 0 : (textureData.mTextureSize.x - 1);
    tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

    Position drawPos = tWorldData->enemies[i].physics.mPosition;
    drawPos.y = getDrawY(drawPos.y, tTexturePosition);

    drawSprite(textureData, drawPos, tTexturePosition);
  }
}

void drawBackground(WorldData* tWorldData) {
  debugLog("Draw background");

  TextureData textureData = getBackgroundTexture();
  Rectangle tTexturePosition;

  tTexturePosition.topLeft.x = 0;
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  Position position;
  position.x = 0;
  position.y = 0;
  position.z = BACKGROUND_POSITION_Z;

  drawSprite(textureData, position, tTexturePosition);
}

void drawPlatforms(WorldData* tWorldData) {
  debugLog("Draw platforms");

  TextureData textureData = getPlatformTexture();

  Rectangle tTexturePosition;
  tTexturePosition.topLeft.x = 0;
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  int i, j;
  for (j = 0; j < MAX_TILES_Y; j++) {
    for (i = 0; i < MAX_TILES_X; i++) {

      if (tWorldData->tiles[j][i] == TILE_PLATFORM) {
        debugLog("Draw single tile");
        debugInteger(i);
        debugInteger(j);
        Position position;
        position.x = TileToRealPositionX(i);
        position.y = TileToRealPositionWithoutPlatformY(j);
        position.y = getDrawY(position.y, tTexturePosition);
        position.z = PLATFORM_POSITION_Z;

        drawSprite(textureData, position, tTexturePosition);
      }
    }
  }
}

void drawExit(WorldData* tWorldData) {
  debugLog("Draw Exit");

  TextureData textureData = getExitTexture();

  Rectangle tTexturePosition;
  tTexturePosition.topLeft.x = 0;
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  Position pos = tWorldData->exitPosition;
  pos.y = getDrawY(pos.y, tTexturePosition);

  drawSprite(textureData, pos, tTexturePosition);
}

void draw(WorldData* tWorldData, CharacterData* tCharacterData) {
  debugLog("Begin drawing");
  updateTiltingMatrix(tWorldData->tiltAngle);
  startDrawing();
  drawBackground(tWorldData);
  drawPlatforms(tWorldData);
  drawCharacter(tWorldData, tCharacterData);
  drawEnemies(tWorldData);
  drawExit(tWorldData);
  stopDrawing();
}

void drawTitleBackground(TitleData* tTitleData) {
  debugLog("Draw Title background");

  TextureData textureData = getTitleTexture();

  Rectangle tTexturePosition;

  tTexturePosition.topLeft.x = 0;
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  Position pos;
  pos.x = 0;
  pos.y = 0;
  pos.z = BACKGROUND_POSITION_Z;

  drawSprite(textureData, pos, tTexturePosition);
}

void drawPressStart(TitleData* tTitleData) {
  debugLog("Draw Title background");

  TextureData textureData = getPressStartTexture();

  Rectangle tTexturePosition;
  tTexturePosition.topLeft.x = 0;
  tTexturePosition.topLeft.y = 0;
  tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
  tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

  Position pos;
  pos.x = PRESS_START_X;
  pos.y = PRESS_START_Y;
  pos.z = CHARACTER_POSITION_Z;

  drawSprite(textureData, pos, tTexturePosition);
}

void drawTitle(TitleData* tTitleData) {
  debugLog("Begin drawing title");
  updateTiltingMatrix(tTitleData->tiltAngle);
  startDrawing();
  drawTitleBackground(tTitleData);
  drawPressStart(tTitleData);
  stopDrawing();
}
