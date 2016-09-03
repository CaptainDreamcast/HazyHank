#include "roundscreen.h"

#include "drawing.h"
#include "round.h"
#include "animation.h"
#include "input.h"
#include "texture.h"

#define TEXT_POSITION_Z 2

typedef struct{
	Duration now;
	Duration screenShown;
	Position textPosition;
	Size1 textSize;
	Color textColor;
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

	drawText(roundScreenText, gRoundData.textPosition, TEXT_POSITION_Z, gRoundData.textSize, gRoundData.textColor);

	waitForScreen();

	return RETURN_NORMAL;
}

void initialize(){
	memset(&gRoundData, 0, sizeof gRoundData);

	sprintf(roundScreenText, "Round: %d", getRound());
	setFont("/rd/fonts/dolmexica.hdr", "/rd/fonts/dolmexica.pkg");

	gRoundData.screenShown = 300;
	gRoundData.textPosition.x = 200;
	gRoundData.textPosition.y = 200;
	gRoundData.textSize = 30;
	gRoundData.textColor = COLOR_WHITE;
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
