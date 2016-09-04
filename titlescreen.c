#include "titlescreen.h"

#include <tari/log.h>
#include <tari/input.h>
#include <tari/math.h>
#include <tari/drawing.h>

#include "titledata.h"
#include "drawing.h"

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

GameReturnType checkDone() {
  if (hasPressedStartFlank()) {
    return RETURN_WON;
  }

  return RETURN_NORMAL;
}

GameReturnType title() {
  updateInput();
  if (hasPressedAbortFlank()) {
    return RETURN_TO_MENU;
  }

  drawTitle(&gTitleData);
  GameReturnType returnType = checkDone();
  calculateTilt();

  waitForScreen();

  return returnType;
}

void initiateTitle() {
  gTitleData.tiltAcceleration = TITLE_TILT_ACCELERATION;
}

GameReturnType titleScreen() {
  memset(&gTitleData, 0, sizeof gTitleData);
  initiateTitle();

  GameReturnType returnType;
  while (1) {
    returnType = title();
    if (returnType != RETURN_NORMAL)
      break;
  }

  return returnType;
}
