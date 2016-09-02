#include "generateLevel.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "basedefinitions.h"
#include "texture.h"
#include "tmath.h"
#include "log.h"

WorldData* gWorldData;

void placePlatform(int y, int x, size_t size){

	int i;
	for(i = x; i < x+size; i++){
		gWorldData->tiles[y][i] = TILE_PLATFORM;
	}	
}

int impossibleToPlacePlatform(int y, int x){
	if(x > 0 && gWorldData->tiles[y][x-1] == TILE_PLATFORM) return 1;

	return gWorldData->tiles[y-1][x] == TILE_PLATFORM;
}

void generatePlatforms(){

	log("Generate Platforms");

	placePlatform(0, 0, MAX_TILES_X);
	
	int j, i, k;
	for(j = 1; j < MAX_TILES_Y; j++){
		for(i = 0; i < MAX_TILES_X-1; i++){
			debugLog("Try place Platform");
			debugInteger(i);
			debugInteger(j);

			if(impossibleToPlacePlatform(j, i)) continue;

			debugLog("Placement possible");
			size_t maxSize = 1;
			for(k = i+1; k < MAX_TILES_X; k++){
				if(impossibleToPlacePlatform(j, k)) break;
				else maxSize++;
			}
			size_t size = (rand()%maxSize)+1;

			debugInteger(maxSize);
			debugInteger(size);

			if(rand()%10 > 7){
				debugLog("Place platform");
				placePlatform(j, i, size);
			}
		}		
	}
}

int impossibleToPlaceEnemy(int y, int x){

	int i;
	for(i = 0; i < gWorldData->enemyAmount; i++){
		if(gWorldData->enemies[i].position.x == TileToRealPositionX(x) && gWorldData->enemies[i].position.y == TileToRealPositionY(y)){
			return 0;
		}
	}

	return gWorldData->tiles[y][x] != TILE_PLATFORM;
}

void placeEnemy(int y, int x){

	double pX = TileToRealPositionX(x);
	double pY = TileToRealPositionY(y);

	gWorldData->enemyAmount++;
	int id = gWorldData->enemyAmount-1;

	gWorldData->enemies[id].isRemoved = 0;
	gWorldData->enemies[id].position.x = pX;
	gWorldData->enemies[id].position.y = pY;
	gWorldData->enemies[id].runAccel = ENEMY_RUN_ACCEL;
	gWorldData->enemies[id].frame = 0;
	gWorldData->enemies[id].velocity.x = 0;
	gWorldData->enemies[id].velocity.y = 0;
	gWorldData->enemies[id].frameAmount = ENEMY_FRAME_AMOUNT;
	gWorldData->enemies[id].animationTicks = 0;
	gWorldData->enemies[id].animationTickAmount = 30;
	gWorldData->enemies[id].state = ENEMY_WALKING;
}

void generateEnemies(){
	log("Generate enemies");

	int placedEnemies = 0;

	int enemiesToBePlaced = (rand()%MAX_ENEMY_AMOUNT)+1;

	logInteger(enemiesToBePlaced);

	int j, i;
	int keepPlacingEnemies = 1;
	while(keepPlacingEnemies){
		for(j = 1; j < MAX_TILES_Y; j++){
			for(i = 0; i < MAX_TILES_X; i++){
				debugLog("Try place Enemy");
				debugInteger(i);
				debugInteger(j);

				if(impossibleToPlaceEnemy(j, i)) continue;

				debugLog("Possible to place enemy");

				if(rand()%10 > 8){
					debugLog("Place enemy");
					placeEnemy(j, i);
					placedEnemies++;
					if(placedEnemies == enemiesToBePlaced) {
						keepPlacingEnemies = 0;
						break;
					}
				}
			}
			if(!keepPlacingEnemies){
				break;
			}		
		}
	
	}
}


int impossibleToPlaceExit(int y, int x){
	return gWorldData->tiles[y][x] != TILE_PLATFORM;
}

PositionI exitPositionTile;

void placeExit(int y, int x){
	gWorldData->exitPosition.x = TileToRealPositionX(x);
	gWorldData->exitPosition.y = TileToRealPositionY(y);

	exitPositionTile.x = x;	
	exitPositionTile.y = y;
}

void generateExit(){
	log("Generate Exit");

	int keepPlacingExit = 1;
	while(keepPlacingExit){
		int j, i;
		for(j = 1; j < MAX_TILES_Y; j++){
			for(i = 0; i < MAX_TILES_X; i++){
				debugLog("Try place Exit");
				debugInteger(i);
				debugInteger(j);

				if(impossibleToPlaceExit(j, i)) continue;

				debugLog("Exit placement possible");

				if(rand()%100 > 98){
					debugLog("Place Exit");
					placeExit(j, i);
					keepPlacingExit = 0;
					break;
				}
			}		
			if(!keepPlacingExit){
				break;
			}
		}
	}
}

int vis[MAX_TILES_Y][MAX_TILES_X];


void checkReachableRecursive(int y, int x){
	if(x < 0 || y < 0 || x >= MAX_TILES_X || y >= MAX_TILES_Y) return;

	if(vis[y][x]) return;

	debugLog("Visit");
	debugInteger(x);
	debugInteger(y);

	vis[y][x] = 1;


	if(gWorldData->tiles[y][x] == TILE_PLATFORM){
		checkReachableRecursive(y+2, x);
		checkReachableRecursive(y+1, x);
		checkReachableRecursive(y+1, x+1);
		checkReachableRecursive(y+1, x-1);
		checkReachableRecursive(y, x+2);
		checkReachableRecursive(y, x-2);
		checkReachableRecursive(y, x+1);
		checkReachableRecursive(y, x-1);
	}
}

int isNotPlayable(){
	log("Check playability");
	memset(vis, 0, sizeof vis);

	int y = RealPositionToTileY(gWorldData->startPosition.y);
	int x = RealPositionToTileX(gWorldData->startPosition.x);

	checkReachableRecursive(y, x);

	return(!vis[exitPositionTile.y][exitPositionTile.x]);
}

void generateLevel(WorldData* tWorldData){
	log("Generate Level");
	gWorldData = tWorldData;
	srand(time(NULL));
	int attempt = 0;
	do{		
		attempt++;
		logInteger(attempt);

		memset(tWorldData, 0, sizeof *tWorldData);

		generatePlatforms();
		generateEnemies();
		generateExit();
	} while(isNotPlayable());
}
