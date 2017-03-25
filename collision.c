#include "collision.h"

#include <tari/log.h>
#include <tari/collision.h>

#include "state.h"

static void swapF(double* x, double* y) {
	double z = *x;
	*x = *y;
	*y = z;
}

CollisionRect getPlatformRectangle(int y, int x) {

  Position pos;

  pos.x = TileToRealPositionX(x);
  pos.y = TileToRealPositionWithoutPlatformY(y);

  CollisionRect rect;
  rect.mTopLeft.x = pos.x;
  rect.mBottomRight.x = pos.x + TILE_SIZE;
  rect.mBottomRight.y = pos.y;
  rect.mTopLeft.y = pos.y + PLATFORM_SIZE_Y;

  swapF(&rect.mBottomRight.y, &rect.mTopLeft.y);

  return rect;
}

CollisionRect getCharacterRectangleFromPosition(Position tPos) {

  CollisionRect rect;

  rect.mTopLeft.x = tPos.x;
  rect.mBottomRight.x = tPos.x + CHARACTER_SIZE_X;
  rect.mBottomRight.y = tPos.y;
  rect.mTopLeft.y = tPos.y + CHARACTER_SIZE_Y;

  swapF(&rect.mBottomRight.y, &rect.mTopLeft.y);

  return rect;
}

int charMovesDown(Velocity tVelocity) {
  return tVelocity.y < 0;
}

int comingFromAbove(CollisionRect tCharRect, CollisionRect tPlatRect, Velocity tVelocity) {
  Position previousPosition;
  previousPosition.x = tCharRect.mTopLeft.x - tVelocity.x;
  previousPosition.y = tCharRect.mBottomRight.y - tVelocity.y;

  return charMovesDown(tVelocity) && !checkCollision(getCharacterRectangleFromPosition(previousPosition), tPlatRect);
}

int checkCollisionPlatform(CollisionRect tCharRect, CollisionRect tPlatRect, Velocity tVelocity) {

  int isValidCollision = tCharRect.mBottomRight.y > tPlatRect.mBottomRight.y;
  return isValidCollision && comingFromAbove(tCharRect, tPlatRect, tVelocity) && checkCollision(tCharRect, tPlatRect);
}

// TODO: replace with good lib function
void resolvePlatformCollision(CharacterData* tCharacterData, int tY) {
  debugLog("Resolve collision for character");
  tCharacterData->physics.mPosition.y = TileToRealPositionY(tY);
  tCharacterData->physics.mVelocity.y = 0;
  tCharacterData->physics.mAcceleration.y = 0;

  if (tCharacterData->state == CHARACTER_JUMPING) {
    changeCharacterState(tCharacterData, CHARACTER_STANDING);
  }

}

void checkCollisionsPlatforms(WorldData* tWorldData, CharacterData* tCharacterData) {
  if (tCharacterData->state == CHARACTER_DYING)
    return;

  int j;
  for (j = 0; j < MAX_TILES_Y; j++) {
    int i;
    for (i = 0; i < MAX_TILES_X; i++) {
      if (tWorldData->tiles[j][i] == TILE_PLATFORM) {
        debugLog("Check collision with platform");
        debugInteger(i);
        debugInteger(j);
        if (checkCollisionPlatform(getCharacterRectangleFromPosition(tCharacterData->physics.mPosition), getPlatformRectangle(j, i), tCharacterData->physics.mVelocity)) {
          resolvePlatformCollision(tCharacterData, j);
        }
      }
    }
  }
}

// TODO: replace with good lib function
void resolvePlatformCollisionEnemy(EnemyData* tEnemyData, int tY) {
  debugLog("Resolve collision for enemy");
  tEnemyData->physics.mPosition.y = TileToRealPositionY(tY);
  tEnemyData->physics.mVelocity.y = 0;
  tEnemyData->physics.mAcceleration.y = 0;
}

void checkCollisionsEnemyAndPlatforms(WorldData* tWorldData, EnemyData* tEnemyData) {

  int j;
  for (j = 0; j < MAX_TILES_Y; j++) {
    int i;
    for (i = 0; i < MAX_TILES_X; i++) {
      if (tWorldData->tiles[j][i] == TILE_PLATFORM) {
        debugLog("Check collision with platform for enemy");
        debugInteger(i);
        debugInteger(j);
        if (checkCollisionPlatform(getCharacterRectangleFromPosition(tEnemyData->physics.mPosition), getPlatformRectangle(j, i), tEnemyData->physics.mVelocity)) {
          resolvePlatformCollisionEnemy(tEnemyData, j);
        }
      }
    }
  }
}
// TODO: move
void killEnemy(CharacterData* tCharacterData, EnemyData* tEnemyData) {
  changeEnemyState(tEnemyData, ENEMY_DYING);
  tCharacterData->physics.mVelocity.y = 0;
  tCharacterData->physics.mAcceleration.y = 10;

}

void killPlayer(CharacterData* tCharData) {
  tCharData->physics.mVelocity.y = 0;
  tCharData->physics.mAcceleration.y = 10;
  changeCharacterState(tCharData, CHARACTER_DYING);
}

void checkCollisionsEnemyAndPlayer(WorldData* tWorldData, EnemyData* tEnemyData, CharacterData* tCharacterData) {
  if (tCharacterData->state == CHARACTER_DYING)
    return;

  CollisionRect charRect = getCharacterRectangleFromPosition(tCharacterData->physics.mPosition);
  CollisionRect enemyRect = getCharacterRectangleFromPosition(tEnemyData->physics.mPosition);


  if (checkCollision(charRect, enemyRect)) {
    int isKillingEnemy = comingFromAbove(charRect, enemyRect, tCharacterData->physics.mVelocity);

    if (isKillingEnemy) {
      killEnemy(tCharacterData, tEnemyData);
    } else {
      killPlayer(tCharacterData);
    }

  }
}

void checkCollisionsEnemies(WorldData* tWorldData, CharacterData* tCharacterData) {
  int i;
  for (i = 0; i < (int)tWorldData->enemyAmount; i++) {
    if (tWorldData->enemies[i].state != ENEMY_DYING) {
      checkCollisionsEnemyAndPlatforms(tWorldData, &tWorldData->enemies[i]);
      checkCollisionsEnemyAndPlayer(tWorldData, &tWorldData->enemies[i], tCharacterData);
    }
  }
}

CollisionRect getScreenRectangle() {
  CollisionRect r;

  r.mTopLeft.x = 0;
  r.mTopLeft.y = SCREEN_SIZE_Y;
  r.mBottomRight.x = SCREEN_SIZE_X;
  r.mBottomRight.y = 0;

  return r;
}

int hasLeftScreen(WorldData* tWorldData, CharacterData* tCharacterData) {
  CollisionRect charRect = getCharacterRectangleFromPosition(tCharacterData->physics.mPosition);
  CollisionRect screenRect = getScreenRectangle();

  return charRect.mTopLeft.y < (screenRect.mBottomRight.y - 100);
}

