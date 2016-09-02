#ifndef STATE_H
#define STATE_H

#include "characterdata.h"
#include "enemydata.h"

void changeCharacterState(CharacterData* tCharacterData, CharacterState tNewState);
void changeEnemyState(EnemyData* tEnemyData, EnemyState tNewState);

#endif
