#include "game.h"

#include "worlddata.h"
#include "characterdata.h"
#include "loadgame.h"
#include "gamescreen.h"
#include "texture.h"
#include "log.h"

WorldData worldData;
CharacterData characterData;

GameReturnType gameLogic(){

	log("Enter game logic");
	GameReturnType returnType;
	loadAllTextures();

	while(1){
		memset(&worldData, 0, sizeof worldData);
		memset(&characterData, 0, sizeof characterData);
		loadGame(&worldData, &characterData);
		returnType = gameScreen(&worldData, &characterData);
		if(returnType == RETURN_TO_MENU) break;
	}
	unloadAllTextures();
	return returnType;
}
