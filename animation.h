#ifndef ANIMATION_H
#define ANIMATION_H

#include "worlddata.h"
#include "characterdata.h"

void handleCharacterAnimation(WorldData* tWorldData, CharacterData* tCharacterData);
void handleEnemyAnimation(WorldData* tWorldData, CharacterData* tCharacterData);

void resetCharacterAnimation(CharacterData* tCharacterData);

#endif

