#include "drawing.h"

#include <stdlib.h>

#include <tari/log.h>
#include <tari/drawing.h>
#include <tari/math.h>

#include "texture.h"

double inverseScreenY(double y) {
  return (SCREEN_SIZE_Y - y);
}

double getDrawY(double y, Rectangle tTexturePosition) {
  double sizeY = tTexturePosition.bottomRight.y - tTexturePosition.topLeft.y;

  return inverseScreenY(y + sizeY);
}

void updateTiltingMatrix(double tTiltAngle) {
  setDrawingParametersToIdentity();
  setDrawingRotationZ(tTiltAngle, makePosition(MIDDLE_OF_SCREEN_X, MIDDLE_OF_SCREEN_Y, 0));
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
  for (i = 0; i < (int)tWorldData->enemyAmount; i++) {
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
  drawBackground(tWorldData);
  drawPlatforms(tWorldData);
  drawCharacter(tWorldData, tCharacterData);
  drawEnemies(tWorldData);
  drawExit(tWorldData);
}

