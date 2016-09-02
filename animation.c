#include "animation.h"

void handleSingleAnimation(Frame* tFrame, Frame tFrameAmount, AnimationTick* tAnimationTicks, AnimationTick tAnimationTickAmount){

	(*tAnimationTicks)++;

	if(*tAnimationTicks >= tAnimationTickAmount){
		(*tAnimationTicks) = 0;
		(*tFrame)++;
		if(*tFrame >= tFrameAmount){
			(*tFrame) = 0;
		}
	}
}

void handleCharacterAnimation(WorldData* tWorldData, CharacterData* tCharacterData){
	CharacterState st = tCharacterData->state;
	handleSingleAnimation(&tCharacterData->frame, tCharacterData->frameAmount[st], &tCharacterData->animationTicks, tCharacterData->animationTickAmount[st]);
}

void handleEnemyAnimation(WorldData* tWorldData, CharacterData* tCharacterData){
	int i;
	for(i = 0; i < tWorldData->enemyAmount; i++){
		handleSingleAnimation(&tWorldData->enemies[i].frame, tWorldData->enemies[i].frameAmount, &tWorldData->enemies[i].animationTicks, tWorldData->enemies[i].animationTickAmount);
	}
}

void resetCharacterAnimation(CharacterData* tCharacterData){
	tCharacterData->frame = 0;
	tCharacterData->animationTicks = 0;
}



