#include "gamescreen.h"

#include <tari/drawing.h>
#include <tari/log.h>
#include <tari/input.h>
#include <tari/system.h>

#include "physics.h"
#include "collision.h"
#include "movement.h"
#include "stagelogic.h"
#include "animation.h"
#include "drawing.h"
#include "loadgame.h"
#include "titlescreen.h"
#include "roundscreen.h"

static WorldData gWorldData;
static CharacterData gCharacterData;


static void drawGameScreen() {
	draw(&gWorldData, &gCharacterData);
}
  

static void updateGameScreen() {
	updateSystem();
	updateInput();

	checkCollisionsPlatforms(&gWorldData, &gCharacterData);
	checkCollisionsEnemies(&gWorldData, &gCharacterData);

	checkJumpingCharacter(&gWorldData, &gCharacterData);
	checkRunningCharacter(&gWorldData, &gCharacterData);
	checkMovementEnemies(&gWorldData, &gCharacterData);

	handlePhysicsForCharacter(&gWorldData, &gCharacterData);
	handlePhysicsForEnemies(&gWorldData, &gCharacterData);

	checkGameOver(&gWorldData, &gCharacterData);
	checkExit(&gWorldData, &gCharacterData);
	handleScreenTilting(&gWorldData, &gCharacterData);

	GameReturnType currentGameReturnStatus = checkGameAbort(&gWorldData, &gCharacterData);
	debugInteger(currentGameReturnStatus);
	if (currentGameReturnStatus == RETURN_LOSS || currentGameReturnStatus == RETURN_TO_MENU) {
		setNewScreen(&TitleScreen);
	}
	else if (currentGameReturnStatus == RETURN_WON) {
		setNewScreen(&RoundScreen);
	}

	handleCharacterAnimation(&gWorldData, &gCharacterData);
	handleEnemyAnimation(&gWorldData, &gCharacterData);
}

static void loadGameScreen() {
	memset(&gWorldData, 0, sizeof gWorldData);
	memset(&gCharacterData, 0, sizeof gCharacterData);
	loadGame(&gWorldData, &gCharacterData);
}

Screen GameScreen = {
	.mLoad = loadGameScreen,
	.mUpdate = updateGameScreen,
	.mDraw = drawGameScreen,
};