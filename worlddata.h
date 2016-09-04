#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "basetypes.h"
#include "enemydata.h"

#include "basedefinitions.h"

typedef enum {
  TILE_EMPTY,
  TILE_PLATFORM
} TileType;

typedef enum {
  GAME_RUNNING,
  GAME_WON,
  GAME_OVER
} WorldState;

#define TileToRealPositionX(x)			(x*TILE_SIZE)
#define TileToRealPositionY(y)			(y*TILE_SIZE+PLATFORM_SIZE_Y)
#define TileToRealPositionWithoutPlatformY(y)	(y*TILE_SIZE)
#define RealPositionToTileX(x)			(x/TILE_SIZE)
#define RealPositionToTileY(y)			((y-PLATFORM_SIZE_Y)/TILE_SIZE)
#define RealPositionToTileWitoutPlatformY(y)	(y/TILE_SIZE)

typedef struct {

  TileType tiles[MAX_TILES_Y][MAX_TILES_X];
  uint32_t enemyAmount;
  EnemyData enemies[MAX_ENEMY_AMOUNT];
  Position exitPosition;
  Position startPosition;
  double tiltVelocity;
  double tiltAngle;
  WorldState state;

} WorldData;

#endif
