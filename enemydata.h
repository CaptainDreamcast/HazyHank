#ifndef ENEMYDATA_H
#define ENEMYDATA_H

#include <kos.h>

#include "basetypes.h"

typedef enum {

	ENEMY_WALKING,
	ENEMY_DYING

} EnemyState;

#define ENEMY_TEXTURE_AMOUNT 2

typedef struct{

	int isRemoved;
	Position position;
	Frame frame;
	Velocity velocity;
	Acceleration acceleration;
	Frame frameAmount;
	double runAccel;
	EnemyState state;
	AnimationTick animationTicks;
	AnimationTick animationTickAmount;
	FaceDirection faceDirection;

} EnemyData;

#endif
