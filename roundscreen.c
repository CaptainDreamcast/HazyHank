#include "roundscreen.h"

#include <tari/drawing.h>
#include <tari/animation.h>
#include <tari/input.h>
#include <tari/texture.h>

#include "round.h"

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

GameReturnType roundLogic() {

  updateInput();
  if (hasPressedAbortFlank()) {
    return RETURN_TO_MENU;
  }

  if (handleDurationAndCheckIfOver(&gRoundData.now, gRoundData.screenShown)) {
    return RETURN_WON;
  }

  startDrawing();
  drawText(roundScreenText, gRoundData.textPosition, gRoundData.textSize, gRoundData.textColor);
  stopDrawing();

  waitForScreen();

  return RETURN_NORMAL;
}

void initialize() {
  memset(&gRoundData, 0, sizeof gRoundData);

  sprintf(roundScreenText, "Round: %d", getRound());
  setFont("/rd/fonts/dolmexica.hdr", "/rd/fonts/dolmexica.pkg");

  gRoundData.screenShown = 60;
  gRoundData.textPosition.x = 200;
  gRoundData.textPosition.y = 200;
  gRoundData.textPosition.z = TEXT_POSITION_Z;
  gRoundData.textSize = 30;
  gRoundData.textColor = COLOR_WHITE;
}

GameReturnType roundScreen() {

  initialize();

  GameReturnType returnType;
  while (1) {
    returnType = roundLogic();
    if (returnType != RETURN_NORMAL)
      break;
  }

  return returnType;
}

