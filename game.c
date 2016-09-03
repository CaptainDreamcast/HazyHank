#include "game.h"

#include "worlddata.h"
#include "characterdata.h"
#include "loadgame.h"
#include "gamescreen.h"
#include "texture.h"
#include "titlescreen.h"
#include "round.h"
#include "roundscreen.h"

#include "log.h"

WorldData worldData;
CharacterData characterData;

GameReturnType gameLogic(){

	log("Enter game logic");
	GameReturnType returnType = RETURN_NORMAL;
	loadAllTextures();

	while(1){
		if(returnType != RETURN_WON){
			resetRound();
			returnType = titleScreen();
			if(returnType == RETURN_TO_MENU) break;
		}
		
		increaseRound();
		returnType = roundScreen();
		if(returnType == RETURN_TO_MENU) break;

		memset(&worldData, 0, sizeof worldData);
		memset(&characterData, 0, sizeof characterData);
		loadGame(&worldData, &characterData);
		returnType = gameScreen(&worldData, &characterData);
		if(returnType == RETURN_TO_MENU) break;
	}
	unloadAllTextures();
	return returnType;
}
