#ifndef STAGELOGIC_H
#define STAGELOGIC_H

#include "worlddata.h"
#include "characterdata.h"

void checkExit(WorldData* tWorldData, CharacterData* tCharacterData);
void handleScreenTilting(WorldData* tWorldData, CharacterData* tCharacterData);
void checkGameOver(WorldData* tWorldData, CharacterData* tCharacterData);
GameReturnType checkGameAbort(WorldData* tWorldData, CharacterData* tCharacterData);

#endif
