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
	loadAllTextures();
	loadGame(&worldData, &characterData);
	GameReturnType returnType = gameScreen(&worldData, &characterData);
	unloadAllTextures();
	return returnType;
}
