#ifndef COLLISION_H
#define COLLISION_H

#include "worlddata.h"
#include "characterdata.h"

void checkCollisionsPlatforms(WorldData* tWorldData, CharacterData* tCharacterData);
void checkCollisionsEnemies(WorldData* tWorldData, CharacterData* tCharacterData);
int hasLeftScreen(WorldData* tWorldData, CharacterData* tCharacterData);

#endif
