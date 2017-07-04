#include "roundscreen.h"

#include <stdio.h>

#include <tari/drawing.h>
#include <tari/animation.h>
#include <tari/input.h>
#include <tari/system.h>
#include <tari/texture.h>

#include "round.h"
#include "titlescreen.h"
#include "gamescreen.h"

#define TEXT_POSITION_Z 2

typedef struct {
  Duration now;
  Duration screenShown;
  Position textPosition;
  TextSize textSize;
  Color textColor;
} RoundScreenData;

RoundScreenData gRoundData;
char roundScreenText[100];

static void updateRoundScreen() {
	updateSystem();
	updateInput();
	if (hasPressedAbortFlank()) {
		setNewScreen(&TitleScreen);
	}

	if (handleDurationAndCheckIfOver(&gRoundData.now, gRoundData.screenShown)) {
		setNewScreen(&GameScreen);
	}
}

static void drawRoundScreen() {
	drawText(roundScreenText, gRoundData.textPosition, gRoundData.textSize, gRoundData.textColor);
}

static void initialize() {
  memset(&gRoundData, 0, sizeof gRoundData);

  sprintf(roundScreenText, "Round: %d", getRound());

  gRoundData.screenShown = 60;
  gRoundData.textPosition.x = 200;
  gRoundData.textPosition.y = 200;
  gRoundData.textPosition.z = TEXT_POSITION_Z;
  gRoundData.textSize = 30;
  gRoundData.textColor = COLOR_WHITE;
}


static void loadRoundScreen() {
	increaseRound();
	initialize();
}

Screen RoundScreen = {
	.mLoad = loadRoundScreen,
	.mUpdate = updateRoundScreen,
	.mDraw = drawRoundScreen,
};