#include "roundscreen.h"

#include "drawing.h"
#include "round.h"
#include "animation.h"
#include "input.h"

typedef struct{
	Duration now;
	Duration screenShown;
	Position textPosition;
} RoundScreenData;

RoundScreenData gRoundData;
char roundScreenText[100];

GameReturnType roundLogic(){
	
	getInput();
	if(hasPressedAbortFlank()){
		return RETURN_TO_MENU;
	}

	if(handleDurationAndCheckIfOver(&gRoundData.now, gRoundData.screenShown)){
		return RETURN_WON;
	}

	drawText(roundScreenText, gRoundData.textPosition);

	waitForScreen();

	return RETURN_NORMAL;
}

void initialize(){
	memset(&gRoundData, 0, sizeof gRoundData);

	sprintf(roundScreenText, "Round: %d", getRound());
	setFont("/fonts/dolmexica.fnt");

	gRoundData.screenShown = 300;
	gRoundData.textPosition.x = 200;
	gRoundData.textPosition.y = 200;
}


GameReturnType roundScreen(){

	initialize();

	GameReturnType returnType;
	while(1){
		returnType = roundLogic();
		if(returnType != RETURN_NORMAL) break;

	}

	return returnType;
}
