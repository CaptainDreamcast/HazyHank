#include "loadgame.h"

#include "generateLevel.h"
#include "basedefinitions.h"
#include "texture.h"
#include "log.h"

#define CHARACTER_FRAME_AMOUNT_STANDING 1
#define CHARACTER_FRAME_AMOUNT_WALKING 2
#define CHARACTER_FRAME_AMOUNT_JUMPING 2
#define CHARACTER_FRAME_AMOUNT_DYING 2

#define CHARACTER_TICK_AMOUNT_STANDING 30
#define CHARACTER_TICK_AMOUNT_WALKING 5
#define CHARACTER_TICK_AMOUNT_JUMPING 5
#define CHARACTER_TICK_AMOUNT_DYING 5

void loadCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	log("Load character");
	tCharacterData->position.x = CHARACTER_START_POSITION_X;
	tCharacterData->position.y = CHARACTER_START_POSITION_Y;
	tCharacterData->frame = 0;
	tCharacterData->velocity.x = 0;
	tCharacterData->velocity.y = 0;
	tCharacterData->frameAmount[CHARACTER_STANDING] = CHARACTER_FRAME_AMOUNT_STANDING;
	tCharacterData->frameAmount[CHARACTER_WALKING] = CHARACTER_FRAME_AMOUNT_WALKING;
	tCharacterData->frameAmount[CHARACTER_JUMPING] = CHARACTER_FRAME_AMOUNT_JUMPING;
	tCharacterData->frameAmount[CHARACTER_DYING] = CHARACTER_FRAME_AMOUNT_DYING;
	tCharacterData->runAccel = CHARACTER_RUN_ACCEL;
	tCharacterData->animationTickAmount[CHARACTER_STANDING] = CHARACTER_TICK_AMOUNT_STANDING;
	tCharacterData->animationTickAmount[CHARACTER_WALKING] = CHARACTER_TICK_AMOUNT_WALKING;
	tCharacterData->animationTickAmount[CHARACTER_JUMPING] = CHARACTER_TICK_AMOUNT_JUMPING;
	tCharacterData->animationTickAmount[CHARACTER_DYING] = CHARACTER_TICK_AMOUNT_DYING;
	tCharacterData->state = CHARACTER_STANDING;
}

void loadGame(WorldData* worldData, CharacterData* characterData){
	log("Begin loading game");
	generateLevel(worldData);
	loadCharacter(worldData, characterData);
}
