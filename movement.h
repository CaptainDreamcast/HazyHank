#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "worlddata.h"
#include "characterdata.h"

void checkJumpingCharacter(WorldData* tWorldData, CharacterData* tCharacterData);
void checkRunningCharacter(WorldData* tWorldData, CharacterData* tCharacterData);
void checkMovementEnemies(WorldData* tWorldData, CharacterData* tCharacterData);

#endif
