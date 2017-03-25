#ifndef ENEMYDATA_H
#define ENEMYDATA_H

#include <tari/physics.h>
#include <tari/animation.h>

#include "basetypes.h"

typedef enum {

  ENEMY_WALKING,
  ENEMY_DYING

} EnemyState;

#define ENEMY_TEXTURE_AMOUNT 2

typedef struct {

  int isRemoved;
  PhysicsObject physics;
  Animation animation;
  double runAccel;
  EnemyState state;
  FaceDirection faceDirection;

} EnemyData;

#endif
