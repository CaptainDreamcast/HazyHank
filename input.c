#include "input.h"

#include <kos.h>

#include "log.h"

maple_device_t* gCont;
cont_state_t* gState;


void getInput(){
	if((gCont = maple_enum_dev(0, 0)) != NULL) {
	    gState = (cont_state_t *)maple_dev_status(gCont);
	}
}

int hasPressedJump(){
	if(!gState) return 0;

	return (gState->buttons & CONT_A);
}
int hasPressedLeft(){
	if(!gState) return 0;

	return ((gState->buttons & CONT_DPAD_LEFT)  || (gState->joyx <= -64));
}

int hasPressedRight(){
	if(!gState) return 0;

	return ((gState->buttons & CONT_DPAD_RIGHT)  || (gState->joyx >= 64));
}
int hasPressedAbort(){
	if(!gState) return 0;

	uint32_t exitCode = (CONT_A | CONT_B | CONT_X | CONT_Y | CONT_START);
	return ((gState->buttons & exitCode) == exitCode);
}

int hasPressedFlank(int tCurrent, int* tFlank){
	int returnValue = 0;

	debugInteger(tCurrent);
	debugInteger((*tFlank));
	if(tCurrent && !(*tFlank)) {
		returnValue = 1;
	}

	(*tFlank) = tCurrent;
	return returnValue;	
}

int gAbortFlank = 0;
int hasPressedAbortFlank(){
	debugLog("check abort flank");
	return hasPressedFlank(hasPressedAbort(), &gAbortFlank);
}

int hasPressedStart(){
	if(!gState) return 0;

	return (gState->buttons & CONT_START);
}
int gStartFlank = 0;
int hasPressedStartFlank(){
	return hasPressedFlank(hasPressedStart(), &gStartFlank);
}
