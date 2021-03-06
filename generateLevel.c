#include "generateLevel.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <tari/log.h>
#include <tari/math.h>
#include <tari/physics.h>

#include "basedefinitions.h"
#include "texture.h"
#include "state.h"

WorldData* gWorldData;

void placePlatform(int y, int x, size_t size) {

  int i;
  for (i = x; i < (int)(x + size); i++) {
    gWorldData->tiles[y][i] = TILE_PLATFORM;
  }
}

int impossibleToPlacePlatform(int y, int x) {
  if (x > 0 && gWorldData->tiles[y][x - 1] == TILE_PLATFORM)
    return 1;

  return gWorldData->tiles[y - 1][x] == TILE_PLATFORM;
}

void generatePlatforms() {

  logg("Generate Platforms");

  placePlatform(0, 0, MAX_TILES_X);

  int j, i, k;
  for (j = 1; j < MAX_TILES_Y; j++) {
    for (i = 0; i < MAX_TILES_X - 1; i++) {
      debugLog("Try place Platform");
      debugInteger(i);
      debugInteger(j);

      if (impossibleToPlacePlatform(j, i))
        continue;

      debugLog("Placement possible");
      size_t maxSize = 1;
      for (k = i + 1; k < MAX_TILES_X; k++) {
        if (impossibleToPlacePlatform(j, k))
          break;
        else
          maxSize++;
      }
      size_t size = (rand() % maxSize) + 1;

      debugInteger(maxSize);
      debugInteger(size);

      if (rand() % 10 > 7) {
        debugLog("Place platform");
        placePlatform(j, i, size);
      }
    }
  }
}

int impossibleToPlaceEnemy(int y, int x) {

  int i;
  for (i = 0; i < (int)gWorldData->enemyAmount; i++) {
    if (gWorldData->enemies[i].physics.mPosition.x == TileToRealPositionX(x) && gWorldData->enemies[i].physics.mPosition.y == TileToRealPositionY(y)) {
      return 0;
    }
  }

  return gWorldData->tiles[y][x] != TILE_PLATFORM;
}

void placeEnemy(int y, int x) {

  double pX = TileToRealPositionX(x);
  double pY = TileToRealPositionY(y);

  gWorldData->enemyAmount++;
  int id = gWorldData->enemyAmount - 1;

  gWorldData->enemies[id].isRemoved = 0;
  gWorldData->enemies[id].physics.mPosition.x = pX;
  gWorldData->enemies[id].physics.mPosition.y = pY;
  gWorldData->enemies[id].physics.mPosition.z = ENEMY_POSITION_Z;
  gWorldData->enemies[id].runAccel = ENEMY_RUN_ACCEL;
  gWorldData->enemies[id].animation.mFrameAmount = ENEMY_FRAME_AMOUNT;
  gWorldData->enemies[id].animation.mDuration = 30;
  changeEnemyState(&gWorldData->enemies[id], ENEMY_WALKING);
  resetAnimation(&gWorldData->enemies[id].animation);
}

void generateEnemies() {
  logg("Generate enemies");

  int placedEnemies = 0;

  int enemiesToBePlaced = (rand() % MAX_ENEMY_AMOUNT) + 1;

  logInteger(enemiesToBePlaced);

  int j, i;
  int keepPlacingEnemies = 1;
  while (keepPlacingEnemies) {
    for (j = 1; j < MAX_TILES_Y; j++) {
      for (i = 0; i < MAX_TILES_X; i++) {
        debugLog("Try place Enemy");
        debugInteger(i);
        debugInteger(j);

        if (impossibleToPlaceEnemy(j, i))
          continue;

        debugLog("Possible to place enemy");

        if (rand() % 10 > 8) {
          debugLog("Place enemy");
          placeEnemy(j, i);
          placedEnemies++;
          if (placedEnemies == enemiesToBePlaced) {
            keepPlacingEnemies = 0;
            break;
          }
        }
      }
      if (!keepPlacingEnemies) {
        break;
      }
    }

  }
}

int impossibleToPlaceExit(int y, int x) {
  return gWorldData->tiles[y][x] != TILE_PLATFORM;
}

TilePosition exitPositionTile;

void placeExit(int y, int x) {
  gWorldData->exitPosition.x = TileToRealPositionX(x);
  gWorldData->exitPosition.y = TileToRealPositionY(y);
  gWorldData->exitPosition.z = EXIT_POSITION_Z;

  exitPositionTile.x = x;
  exitPositionTile.y = y;
}

void generateExit() {
  logg("Generate Exit");

  int keepPlacingExit = 1;
  while (keepPlacingExit) {
    int j, i;
    for (j = 1; j < MAX_TILES_Y; j++) {
      for (i = 0; i < MAX_TILES_X; i++) {
        debugLog("Try place Exit");
        debugInteger(i);
        debugInteger(j);

        if (impossibleToPlaceExit(j, i))
          continue;

        debugLog("Exit placement possible");

        if (rand() % 100 > 98) {
          debugLog("Place Exit");
          placeExit(j, i);
          keepPlacingExit = 0;
          break;
        }
      }
      if (!keepPlacingExit) {
        break;
      }
    }
  }
}

int vis[MAX_TILES_Y][MAX_TILES_X];

void checkReachableRecursive(int y, int x) {
  if (x < 0 || y < 0 || x >= MAX_TILES_X || y >= MAX_TILES_Y)
    return;

  if (vis[y][x])
    return;

  debugLog("Visit");
  debugInteger(x);
  debugInteger(y);

  vis[y][x] = 1;

  if (gWorldData->tiles[y][x] == TILE_PLATFORM) {
    checkReachableRecursive(y + 2, x);
    checkReachableRecursive(y + 1, x);
    checkReachableRecursive(y + 1, x + 1);
    checkReachableRecursive(y + 1, x - 1);
    checkReachableRecursive(y, x + 2);
    checkReachableRecursive(y, x - 2);
    checkReachableRecursive(y, x + 1);
    checkReachableRecursive(y, x - 1);
  }
}

int isNotPlayable() {
  logg("Check playability");
  memset(vis, 0, sizeof vis);

  int y = (int)RealPositionToTileY(gWorldData->startPosition.y);
  int x = (int)RealPositionToTileX(gWorldData->startPosition.x);

  checkReachableRecursive(y, x);

  return (!vis[exitPositionTile.y][exitPositionTile.x]);
}

void generateGravity() {
  logg("Generate gravity");
  Gravity grav;
  grav.x = 0;
  grav.y = -GRAVITY;
  grav.z = 0;
  setGravity(grav);
}

void generateLevel(WorldData* tWorldData) {
  logg("Generate Level");
  gWorldData = tWorldData;
  srand((unsigned int)time(NULL));
  int attempt = 0;
  do {
    attempt++;
    logInteger(attempt);

    memset(tWorldData, 0, sizeof *tWorldData);

    generatePlatforms();
    generateEnemies();
    generateExit();
  } while (isNotPlayable());

  generateGravity();
}
