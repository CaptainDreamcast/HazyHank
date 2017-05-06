#include "loadgame.h"

#include <tari/physics.h>
#include <tari/log.h>

#include "generateLevel.h"
#include "basedefinitions.h"
#include "texture.h"
#include "state.h"

#define CHARACTER_FRAME_AMOUNT_STANDING 1
#define CHARACTER_FRAME_AMOUNT_WALKING 2
#define CHARACTER_FRAME_AMOUNT_JUMPING 2
#define CHARACTER_FRAME_AMOUNT_DYING 2

#define CHARACTER_TICK_AMOUNT_STANDING 30
#define CHARACTER_TICK_AMOUNT_WALKING 5
#define CHARACTER_TICK_AMOUNT_JUMPING 5
#define CHARACTER_TICK_AMOUNT_DYING 5

void loadCharacter(WorldData* tWorldData, CharacterData* tCharacterData) {
  logg("Load character");
  tCharacterData->physics.mPosition.x = CHARACTER_START_POSITION_X;
  tCharacterData->physics.mPosition.y = CHARACTER_START_POSITION_Y;
  tCharacterData->physics.mPosition.z = CHARACTER_POSITION_Z;
  tCharacterData->frameAmount[CHARACTER_STANDING] = CHARACTER_FRAME_AMOUNT_STANDING;
  tCharacterData->frameAmount[CHARACTER_WALKING] = CHARACTER_FRAME_AMOUNT_WALKING;
  tCharacterData->frameAmount[CHARACTER_JUMPING] = CHARACTER_FRAME_AMOUNT_JUMPING;
  tCharacterData->frameAmount[CHARACTER_DYING] = CHARACTER_FRAME_AMOUNT_DYING;
  tCharacterData->runAccel = CHARACTER_RUN_ACCEL;
  tCharacterData->animationDuration[CHARACTER_STANDING] = CHARACTER_TICK_AMOUNT_STANDING;
  tCharacterData->animationDuration[CHARACTER_WALKING] = CHARACTER_TICK_AMOUNT_WALKING;
  tCharacterData->animationDuration[CHARACTER_JUMPING] = CHARACTER_TICK_AMOUNT_JUMPING;
  tCharacterData->animationDuration[CHARACTER_DYING] = CHARACTER_TICK_AMOUNT_DYING;
  changeCharacterState(tCharacterData, CHARACTER_STANDING);
  resetAnimation(&tCharacterData->animation);
}

void loadGame(WorldData* worldData, CharacterData* characterData) {
  logg("Begin loading game");
  generateLevel(worldData);
  loadCharacter(worldData, characterData);
}
