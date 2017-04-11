#include "animation.h"

#include <tari/animation.h>

void handleCharacterAnimation(WorldData* tWorldData, CharacterData* tCharacterData) {
  CharacterState st = tCharacterData->state;
  // TODO: move to state change
  tCharacterData->animation.mFrameAmount = tCharacterData->frameAmount[st];
  tCharacterData->animation.mDuration = tCharacterData->animationDuration[st];

  animate(&tCharacterData->animation);
}

void handleEnemyAnimation(WorldData* tWorldData, CharacterData* tCharacterData) {
  int i;
  for (i = 0; i < (int)tWorldData->enemyAmount; i++) {
    animate(&tWorldData->enemies[i].animation);
  }
}

void resetCharacterAnimation(CharacterData* tCharacterData) {
  resetAnimation(&tCharacterData->animation);
}
