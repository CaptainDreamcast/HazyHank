#include "state.h"

#include <tari/log.h>

#include "animation.h"

void changeCharacterState(CharacterData* tCharacterData, CharacterState tNewState) {
  debugLog("Changing state char");
  debugInteger(tNewState);
  tCharacterData->state = tNewState;
  resetCharacterAnimation(tCharacterData);
}

void changeEnemyState(EnemyData* tEnemyData, EnemyState tNewState) {
  debugLog("Changing state enemy");
  debugInteger(tNewState);
  tEnemyData->state = tNewState;
}
