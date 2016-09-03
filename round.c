#include "round.h"

int gRound;

void resetRound(){
	gRound = 0;
}

void increaseRound(){
	gRound++;
}

int getRound(){
	return gRound;
}

