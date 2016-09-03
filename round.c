#include "round.h"

int gRound;

void resetRound(){
	gRound = 1;
}

void increaseRound(){
	gRound++;
}

int getRound(){
	return gRound;
}

