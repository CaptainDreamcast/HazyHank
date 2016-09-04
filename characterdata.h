#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <kos.h>
#include <tari/physics.h>
#include <tari/animation.h>

#include "basetypes.h"

typedef enum {
  CHARACTER_STANDING = 0,
  CHARACTER_WALKING,
  CHARACTER_JUMPING,
  CHARACTER_DYING
} CharacterState;

typedef struct {

  PhysicsObject physics;
  Animation animation;
  Frame frameAmount[4];
  Duration animationDuration[4];
  double runAccel;
  CharacterState state;
  FaceDirection faceDirection;

} CharacterData;

#endif

