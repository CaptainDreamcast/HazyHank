#include "collision.h"

#include "state.h"

#include "log.h"

Rectangle getPlatformRectangle(int y, int x){

	Position pos;
	
	pos.x = TileToRealPositionX(x);
	pos.y = TileToRealPositionWithoutPlatformY(y);

	Rectangle rect;
	rect.topLeft.x = pos.x;
	rect.bottomRight.x = pos.x+TILE_SIZE;
	rect.bottomRight.y = pos.y;
	rect.topLeft.y = pos.y + PLATFORM_SIZE_Y;

	return rect;
}

Rectangle getCharacterRectangleFromPosition(Position tPos){

	Rectangle rect;

	rect.topLeft.x = tPos.x;
	rect.bottomRight.x = tPos.x+CHARACTER_SIZE_X;
	rect.bottomRight.y = tPos.y;
	rect.topLeft.y = tPos.y + CHARACTER_SIZE_Y;

	return rect;
}

int collisionRect(Rectangle tRect1, Rectangle tRect2){

	if(tRect1.topLeft.x > tRect2.bottomRight.x) return 0;
	if(tRect1.topLeft.y < tRect2.bottomRight.y) return 0;
	if(tRect2.topLeft.x > tRect1.bottomRight.x) return 0;
	if(tRect2.topLeft.y < tRect1.bottomRight.y) return 0;

	debugLog("Collision found");
	return 1;
}

int charMovesDown(Velocity tVelocity){
	return tVelocity.y < 0;
}

int comingFromAbove(Rectangle tCharRect, Rectangle tPlatRect, Velocity tVelocity){
	Position previousPosition;
	previousPosition.x = tCharRect.topLeft.x - tVelocity.x;
	previousPosition.y = tCharRect.bottomRight.y - tVelocity.y;
	
	return charMovesDown(tVelocity)  && !collisionRect(getCharacterRectangleFromPosition(previousPosition), tPlatRect);
}

int checkCollisionPlatform(Rectangle tCharRect, Rectangle tPlatRect, Velocity tVelocity){

	int isValidCollision = tCharRect.bottomRight.y > tPlatRect.bottomRight.y;
	return isValidCollision && comingFromAbove(tCharRect, tPlatRect, tVelocity) && collisionRect(tCharRect, tPlatRect);
}

void resolvePlatformCollision(CharacterData* tCharacterData, int tY){
	debugLog("Resolve collision for character");
	tCharacterData->position.y = TileToRealPositionY(tY);
	tCharacterData->velocity.y = 0;
	tCharacterData->acceleration.y = 0;

	if(tCharacterData->state == CHARACTER_JUMPING){
		changeCharacterState(tCharacterData, CHARACTER_STANDING);
	}

}

void checkCollisionsPlatforms(WorldData* tWorldData, CharacterData* tCharacterData){
	if(tCharacterData->state == CHARACTER_DYING) return;

	int j;
	for(j = 0; j < MAX_TILES_Y; j++){
		int i;
		for(i = 0; i < MAX_TILES_X; i++){
			if(tWorldData->tiles[j][i] == TILE_PLATFORM){
				debugLog("Check collision with platform");
				debugInteger(i); 
				debugInteger(j);
				if(checkCollisionPlatform(getCharacterRectangleFromPosition(tCharacterData->position), getPlatformRectangle(j, i), tCharacterData->velocity)){
					resolvePlatformCollision(tCharacterData, j);
				}
		   	}
		}
	}
}

void resolvePlatformCollisionEnemy(EnemyData* tEnemyData, int tY){
	debugLog("Resolve collision for enemy");
	tEnemyData->position.y = TileToRealPositionY(tY);
	tEnemyData->velocity.y = 0;
	tEnemyData->acceleration.y = 0;
}

void checkCollisionsEnemyAndPlatforms(WorldData* tWorldData, EnemyData* tEnemyData){

	int j;
	for(j = 0; j < MAX_TILES_Y; j++){
		int i;
		for(i = 0; i < MAX_TILES_X; i++){
			if(tWorldData->tiles[j][i] == TILE_PLATFORM){
				debugLog("Check collision with platform for enemy");
				debugInteger(i); 
				debugInteger(j);
				if(checkCollisionPlatform(getCharacterRectangleFromPosition(tEnemyData->position), getPlatformRectangle(j, i), tEnemyData->velocity)){
					resolvePlatformCollisionEnemy(tEnemyData, j);
				}
		   	}
		}
	}
}

void killEnemy(CharacterData* tCharacterData, EnemyData* tEnemyData){
	changeEnemyState(tEnemyData, ENEMY_DYING);
	tCharacterData->acceleration.y += 10;

}

void killPlayer(CharacterData* tCharData){
	tCharData->acceleration.y += 10;
	changeCharacterState(tCharData, CHARACTER_DYING);
}

void checkCollisionsEnemyAndPlayer(WorldData* tWorldData, EnemyData* tEnemyData, CharacterData* tCharacterData){
	if(tCharacterData->state == CHARACTER_DYING) return;

	Rectangle charRect = getCharacterRectangleFromPosition(tCharacterData->position);
	Rectangle enemyRect = getCharacterRectangleFromPosition(tEnemyData->position);

	if(collisionRect(charRect, enemyRect)){
		int isKillingEnemy = comingFromAbove(charRect, enemyRect, tCharacterData->velocity);

		if(isKillingEnemy){
			killEnemy(tCharacterData, tEnemyData);
		} else {
			killPlayer(tCharacterData);
		}

	}
}

void checkCollisionsEnemies(WorldData* tWorldData, CharacterData* tCharacterData){
	int i;	
	for(i = 0; i < tWorldData->enemyAmount; i++){
		if(tWorldData->enemies[i].state != ENEMY_DYING){
			checkCollisionsEnemyAndPlatforms(tWorldData, &tWorldData->enemies[i]);
			checkCollisionsEnemyAndPlayer(tWorldData, &tWorldData->enemies[i], tCharacterData);
		}
	}
}

Rectangle getScreenRectangle(){
	Rectangle r;

	r.topLeft.x = 0;
	r.topLeft.y = SCREEN_SIZE_Y;
	r.bottomRight.x = SCREEN_SIZE_X;
	r.bottomRight.y = 0;

	return r;
}

int hasLeftScreen(WorldData* tWorldData, CharacterData* tCharacterData){
	Rectangle charRect = getCharacterRectangleFromPosition(tCharacterData->position);
	Rectangle screenRect = getScreenRectangle();
	
	return charRect.topLeft.y < (screenRect.bottomRight.y-100);
}


