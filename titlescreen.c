#include "titlescreen.h"

#include <tari/log.h>
#include <tari/input.h>
#include <tari/math.h>
#include <tari/drawing.h>
#include <tari/system.h>

#include "titledata.h"
#include "drawing.h"
#include "texture.h"
#include "round.h"
#include "roundscreen.h"

#define TITLE_TILT_ACCELERATION 0.001
#define TITLE_TILT_VELOCITY_MAX	0.02

TitleData gTitleData;

void calculateTilt() {
  gTitleData.tiltVelocity += gTitleData.tiltAcceleration;

  if (gTitleData.tiltVelocity > TITLE_TILT_VELOCITY_MAX) {
    gTitleData.tiltVelocity = TITLE_TILT_VELOCITY_MAX;
  } else if (gTitleData.tiltVelocity < -TITLE_TILT_VELOCITY_MAX) {
    gTitleData.tiltVelocity = -TITLE_TILT_VELOCITY_MAX;
  }
  gTitleData.tiltAngle += gTitleData.tiltVelocity;

  debugDouble(gTitleData.tiltAngle);
  if ((gTitleData.tiltAngle < -0.5 && gTitleData.tiltAcceleration < 0) || (gTitleData.tiltAngle > 0.5 && gTitleData.tiltAcceleration > 0)) {
    debugLog("switch tilt direction");
    gTitleData.tiltAcceleration *= -1;
  }
}

static void checkDone() {

  if (hasPressedStartFlank()) {
	  setNewScreen(&RoundScreen);
  }  
}

static void updateTitleScreen() {
  updateSystem();
  updateInput();
  if (hasPressedAbortFlank()) {
	  abortScreenHandling();
  }

  checkDone();
  calculateTilt();
}

static void drawTitleBackground(TitleData* tTitleData) {
	debugLog("Draw Title background");

	TextureData textureData = getTitleTexture();

	Rectangle tTexturePosition;

	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
	tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

	Position pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = BACKGROUND_POSITION_Z;

	drawSprite(textureData, pos, tTexturePosition);
}

static void drawPressStart(TitleData* tTitleData) {
	debugLog("Draw Title background");

	TextureData textureData = getPressStartTexture();

	Rectangle tTexturePosition;
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.mTextureSize.x - 1;
	tTexturePosition.bottomRight.y = textureData.mTextureSize.y - 1;

	Position pos;
	pos.x = PRESS_START_X;
	pos.y = PRESS_START_Y;
	pos.z = CHARACTER_POSITION_Z;

	drawSprite(textureData, pos, tTexturePosition);
}

static void drawTitle() {
	debugLog("Begin drawing title");
	updateTiltingMatrix(gTitleData.tiltAngle);
	drawTitleBackground(&gTitleData);
	drawPressStart(&gTitleData);
}


static void initiateTitle() {
  gTitleData.tiltAcceleration = TITLE_TILT_ACCELERATION;
}

static void loadTitleScreen() {
	resetRound();
	memset(&gTitleData, 0, sizeof gTitleData);
	initiateTitle();
}


Screen TitleScreen = {
	.mLoad = loadTitleScreen,
	.mUpdate = updateTitleScreen,
	.mDraw = drawTitle,
};