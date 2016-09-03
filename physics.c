#include "physics.h"

#include <tari/physics.h>
#include <tari/log.h>

void handlePhysicsForCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	debugLog("Start handling physics");
	debugDouble(tCharacterData->physics.mAcceleration.x);
	debugDouble(tCharacterData->physics.mAcceleration.y);
	debugDouble(tCharacterData->physics.mVelocity.x);
	debugDouble(tCharacterData->physics.mVelocity.y);

	handlePhysics(&tCharacterData->physics);
	tCharacterData->physics.mVelocity.x *= 0.5; // TODO: find out better rule behind this and add to lib

	debugDouble(tCharacterData->physics.mPosition.x);
	debugDouble(tCharacterData->physics.mPosition.y);
	debugDouble(tCharacterData->physics.mVelocity.x);
	debugDouble(tCharacterData->physics.mVelocity.y);
}

void handlePhysicsForEnemies(WorldData* tWorldData, CharacterData* tCharacterData){
	
	int i;
	for(i = 0; i < tWorldData->enemyAmount; i++){
		handlePhysics(&tWorldData->enemies[i].physics);
		tWorldData->enemies[i].physics.mVelocity.x *= 0.5; // TODO: find out better rule behind this and add to lib
	}

}
