#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <kos.h>

#include "basetypes.h"

typedef enum {
	CHARACTER_STANDING = 0,
	CHARACTER_WALKING,
	CHARACTER_JUMPING,
	CHARACTER_DYING
} CharacterState;

typedef struct {

	Position position;
	Frame frame;
	Velocity velocity;
	Acceleration acceleration;
	Frame frameAmount[4];
	double runAccel;
	CharacterState state;
	AnimationTick animationTicks;
	AnimationTick animationTickAmount[4];
	FaceDirection faceDirection;

} CharacterData;

#endif

