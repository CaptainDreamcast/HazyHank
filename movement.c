#include "movement.h"

#include <tari/input.h>
#include <tari/log.h>

#include "state.h"

#define CHARACTER_JUMPING_ACCEL	15.0

int characterCanJump(CharacterData* tCharacterData){
	return tCharacterData->state == CHARACTER_STANDING || tCharacterData->state == CHARACTER_WALKING;
}

int isJumpingInvoluntarily(CharacterData* tCharacterData){
	return (tCharacterData->state == CHARACTER_STANDING || tCharacterData->state == CHARACTER_WALKING) && tCharacterData->physics.mVelocity.y != 0;
}


void checkJumpingCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	if(tCharacterData->state == CHARACTER_DYING) return;

	if(hasPressedAFlank() && characterCanJump(tCharacterData)){
		tCharacterData->physics.mAcceleration.y += CHARACTER_JUMPING_ACCEL;
		changeCharacterState(tCharacterData, CHARACTER_JUMPING);
	} else if(isJumpingInvoluntarily(tCharacterData)){
		changeCharacterState(tCharacterData, CHARACTER_JUMPING);
	}
}

void move(CharacterData* tCharacterData, int tMultiplier, FaceDirection tFaceDirection){
	tCharacterData->physics.mAcceleration.x = tMultiplier*CHARACTER_RUN_ACCEL;
	tCharacterData->faceDirection = tFaceDirection;
	if(tCharacterData->state != CHARACTER_JUMPING && tCharacterData->state != CHARACTER_WALKING){
		changeCharacterState(tCharacterData, CHARACTER_WALKING);
	}
}

int characterCanRun(CharacterData* tCharacterData){
	return 1;
}

void checkRunningCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	if(tCharacterData->state == CHARACTER_DYING) return;

	if(characterCanRun(tCharacterData)){
		if(hasPressedLeft()){
			move(tCharacterData, -1, FACE_LEFT);
		} else if(hasPressedRight()){
			move(tCharacterData, 1, FACE_RIGHT);
		} else if(tCharacterData->state == CHARACTER_WALKING){
			changeCharacterState(tCharacterData, CHARACTER_STANDING);
		}
	}
}


int isMovingLeft(EnemyData* tEnemyData){
	return tEnemyData->faceDirection == FACE_LEFT;
}

#define LEFT_BORDER_THRESHOLD 5
#define RIGHT_BORDER_THRESHOLD 0

int isOnLeftPlatformBorder(EnemyData* tEnemyData){
	int positionInTile = ((int)tEnemyData->physics.mPosition.x) % TILE_SIZE;
	return positionInTile < LEFT_BORDER_THRESHOLD;
}
int isOnRightPlatformBorder(EnemyData* tEnemyData){
	int positionInTile = ((int)tEnemyData->physics.mPosition.x) % TILE_SIZE;
	return positionInTile > RIGHT_BORDER_THRESHOLD;
}


int hasNoPlatformToTheLeft(WorldData* tWorldData, EnemyData* tEnemyData){
	int tX = RealPositionToTileX(tEnemyData->physics.mPosition.x);
	int tY = RealPositionToTileWitoutPlatformY(tEnemyData->physics.mPosition.y);

	return (tX == 0 || tWorldData->tiles[tY][tX-1] == TILE_EMPTY);
}
int hasNoPlatformToTheRight(WorldData* tWorldData, EnemyData* tEnemyData){
	int tX = RealPositionToTileX(tEnemyData->physics.mPosition.x);
	int tY = RealPositionToTileWitoutPlatformY(tEnemyData->physics.mPosition.y);

	return (tX == (MAX_TILES_X-1) || tWorldData->tiles[tY][tX+1] == TILE_EMPTY);
}

int cannotMoveLeft(WorldData* tWorldData, EnemyData* tEnemyData){
	return isOnLeftPlatformBorder(tEnemyData) && hasNoPlatformToTheLeft(tWorldData, tEnemyData);
}
int cannotMoveRight(WorldData* tWorldData, EnemyData* tEnemyData){
	return isOnRightPlatformBorder(tEnemyData) && hasNoPlatformToTheRight(tWorldData, tEnemyData);
}

void turnLeft(EnemyData* tEnemyData){
	tEnemyData->faceDirection = FACE_LEFT;
}
void turnRight(EnemyData* tEnemyData){
	tEnemyData->faceDirection = FACE_RIGHT;
}

void moveLeft(EnemyData* tEnemyData){
	tEnemyData->physics.mAcceleration.x = -ENEMY_RUN_ACCEL;
}
void moveRight(EnemyData* tEnemyData){
	tEnemyData->physics.mAcceleration.x = ENEMY_RUN_ACCEL;
}

void checkSingleEnemyMovement(WorldData* tWorldData, EnemyData* tEnemyData){
	
	if(isMovingLeft(tEnemyData)){
		if(cannotMoveLeft(tWorldData, tEnemyData)) {
			turnRight(tEnemyData);
		} else {
			moveLeft(tEnemyData);	
		}
	} else {
		if(cannotMoveRight(tWorldData, tEnemyData)) {
			turnLeft(tEnemyData);
		} else {
			moveRight(tEnemyData);	
		}
	}
}

void checkMovementEnemies(WorldData* tWorldData, CharacterData* tCharacterData){
	
	int i;
	for(i = 0; i < tWorldData->enemyAmount; i++){
		debugLog("Movement enemy");
		debugInteger(i);
		debugInteger(tWorldData->enemies[i].state);
		if(tWorldData->enemies[i].state == ENEMY_DYING) continue;
		checkSingleEnemyMovement(tWorldData, &tWorldData->enemies[i]);
	}

}
