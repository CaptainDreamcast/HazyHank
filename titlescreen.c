#include "titlescreen.h"

#include "titledata.h"
#include "drawing.h"
#include "input.h"

TitleData gTitleData;

void calculateTilt(){

}

GameReturnType checkDone(){
	if(hasPressedStartFlank()){
		return RETURN_WON;
	}	

	return RETURN_NORMAL;
}

GameReturnType title(){

	if(hasPressedAbortFlank()) {
		return RETURN_TO_MENU;
	}

	drawTitle(&gTitleData);
	GameReturnType returnType = checkDone();
	calculateTilt();

	waitForScreen();

	return returnType;
}

void initiateTitle(){

}

GameReturnType titleScreen(){
	memset(&gTitleData, 0, sizeof gTitleData);
	initiateTitle();

	GameReturnType returnType;
	while(1){
		returnType = title();
		if(returnType != RETURN_NORMAL) break;
	}

	return returnType;
}
