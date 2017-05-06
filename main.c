
#include <tari/log.h>
#include <tari/pvr.h>
#include <tari/physics.h>
#include <tari/framerateselectscreen.h>
#include <tari/drawing.h>
#include <tari/system.h>

#include "basetypes.h"
#include "game.h"

#ifdef DREAMCAST
#include <kos.h>

KOS_INIT_FLAGS(INIT_DEFAULT);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

uint32_t useRomDisk = 1;

#endif

// #define DEVELOP

void exitGame() {
#ifdef DEVELOP
  abortSystem();
#else
  returnToMenu();
#endif
}

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	setGameName("HAZY HANK");

	initSystem();
	initDrawing();
  initiatePVR();
  initPhysics();

  logg("Check framerate");
  setFont("/rd/fonts/dolmexica.hdr", "/rd/fonts/dolmexica.pkg");
  FramerateSelectReturnType framerateReturnType = selectFramerate();
  if (framerateReturnType == FRAMERATE_SCREEN_RETURN_ABORT) {
    exitGame();
  }

  logg("Begin game routine");
  GameReturnType returnType = gameLogic();

  if (returnType == RETURN_TO_MENU) {
    exitGame();
  }

  return 0;
}

int wmain(int argc, char** argv) {
	return main(argc, argv);
}
