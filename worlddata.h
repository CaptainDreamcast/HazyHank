#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "basetypes.h"
#include "enemydata.h"

#include "basedefinitions.h"

typedef enum{
	GAME_RUNNING,
	GAME_WON,
	GAME_OVER
} WorldState;

typedef struct{

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
