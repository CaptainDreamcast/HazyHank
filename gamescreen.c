#include "gamescreen.h"

#include "input.h"
#include "physics.h"
#include "collision.h"
#include "movement.h"
#include "stagelogic.h"
#include "animation.h"
#include "drawing.h"

#include "log.h"

GameReturnType gameLoop(WorldData* tWorldData, CharacterData* tCharacterData){
	draw(tWorldData, tCharacterData);

	getInput();

	checkCollisionsPlatforms(tWorldData, tCharacterData);
	checkCollisionsEnemies(tWorldData, tCharacterData);

	checkJumpingCharacter(tWorldData, tCharacterData);
	checkRunningCharacter(tWorldData, tCharacterData);
	checkMovementEnemies(tWorldData, tCharacterData);

	handlePhysicsForCharacter(tWorldData, tCharacterData);
	handlePhysicsForEnemies(tWorldData, tCharacterData);

	checkGameOver(tWorldData, tCharacterData);
	checkExit(tWorldData, tCharacterData);
	handleScreenTilting(tWorldData, tCharacterData);

	GameReturnType currentGameReturnStatus = checkGameAbort(tWorldData, tCharacterData);
	debugInteger(currentGameReturnStatus);
	if(currentGameReturnStatus != RETURN_NORMAL){
		return currentGameReturnStatus;
	}
	
	handleCharacterAnimation(tWorldData, tCharacterData);
	handleEnemyAnimation(tWorldData, tCharacterData);

	waitForScreen();

	return RETURN_NORMAL;
}

GameReturnType gameScreen(WorldData* tWorldData, CharacterData* tCharacterData){

	log("Enter game screen");
	GameReturnType returnType;
	while(1){
		debugLog("Start game loop");
		returnType = gameLoop(tWorldData, tCharacterData);
		if(returnType != RETURN_NORMAL) break;
	}

	return returnType;
}

