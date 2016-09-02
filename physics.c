#include "physics.h"

#include "log.h"

void handlePhysics(Position* tPosition, Velocity* tVelocity, Acceleration* tAcceleration, double gravity){

	tPosition->x += tVelocity->x;
	tPosition->y += tVelocity->y;

	tVelocity->x *= 0.5;

	tVelocity->x += tAcceleration->x;
	tVelocity->y += tAcceleration->y;

	tAcceleration->x = 0;
	tAcceleration->y = -gravity;
}

void handlePhysicsForCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	debugLog("Start handling physics");
	debugDouble(tCharacterData->acceleration.x);
	debugDouble(tCharacterData->acceleration.y);
	debugDouble(tCharacterData->velocity.x);
	debugDouble(tCharacterData->velocity.y);

	handlePhysics(&tCharacterData->position, &tCharacterData->velocity, &tCharacterData->acceleration, GRAVITY);

	debugDouble(tCharacterData->position.x);
	debugDouble(tCharacterData->position.y);
	debugDouble(tCharacterData->velocity.x);
	debugDouble(tCharacterData->velocity.y);
}

void handlePhysicsForEnemies(WorldData* tWorldData, CharacterData* tCharacterData){
	
	int i;
	for(i = 0; i < tWorldData->enemyAmount; i++){
		handlePhysics(&tWorldData->enemies[i].position, &tWorldData->enemies[i].velocity, &tWorldData->enemies[i].acceleration, GRAVITY);
	}

}
