#ifndef PHYSICS_H
#define PHYSICS_H

#include "worlddata.h"
#include "characterdata.h"

void handlePhysicsForCharacter(WorldData* tWorldData, CharacterData* tCharacterData);
void handlePhysicsForEnemies(WorldData* tWorldData, CharacterData* tCharacterData);

#endif
