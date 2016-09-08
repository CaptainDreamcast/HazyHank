#include "stagelogic.h"

#include <stdlib.h>

#include <tari/log.h>
#include <tari/input.h>

#include "collision.h"

int NO_TILT = 0;

void checkExit(WorldData* tWorldData, CharacterData* tCharacterData) {
  int exitTileX = RealPositionToTileX(tWorldData->exitPosition.x);
  int exitTileY = RealPositionToTileWitoutPlatformY(tWorldData->exitPosition.y);

  int pTileX = RealPositionToTileX((tCharacterData->physics.mPosition.x+(TILE_SIZE/2)));
  int pTileY = RealPositionToTileWitoutPlatformY(tCharacterData->physics.mPosition.y);

  if (exitTileX == pTileX && exitTileY == pTileY) {
    tWorldData->state = GAME_WON;
  }
}

#define MAX_TILT_VELOCITY 0.075

int direction = 0;

void changeDirection() {
  direction = (direction + 1) % 2;
}

void handleScreenTilting(WorldData* tWorldData, CharacterData* tCharacterData) {

  if (NO_TILT) {
    return;
  }

  if (direction) {
    double tiltAcceleration = ((rand() % 500) * 0.000001);
    debugDouble(tiltAcceleration);
    tWorldData->tiltVelocity += tiltAcceleration;
  } else {
    double tiltAcceleration = -((rand() % 500) * 0.000001);
    debugDouble(tiltAcceleration);
    tWorldData->tiltVelocity += tiltAcceleration;
  }

  if (rand() % 500 == 0) {
    changeDirection();
  }

  if (tWorldData->tiltVelocity > MAX_TILT_VELOCITY) {
    tWorldData->tiltVelocity = MAX_TILT_VELOCITY;
    changeDirection();
  } else if (tWorldData->tiltVelocity < -MAX_TILT_VELOCITY) {
    tWorldData->tiltVelocity = -MAX_TILT_VELOCITY;
    changeDirection();
  }

  tWorldData->tiltAngle += tWorldData->tiltVelocity;
}

GameReturnType checkGameAbort(WorldData* tWorldData, CharacterData* tCharacterData) {
  if (hasPressedAbortFlank()) {
    return RETURN_TO_MENU;
  } else if (tWorldData->state == GAME_WON) {
    return RETURN_WON;
  } else if (tWorldData->state == GAME_OVER) {
    return RETURN_LOSS;
  } else {
    return RETURN_NORMAL;
  }
}

void checkGameOver(WorldData* tWorldData, CharacterData* tCharacterData) {
  if (hasLeftScreen(tWorldData, tCharacterData)) {
    tWorldData->state = GAME_OVER;
  }
}
