#include <kos.h> 

KOS_INIT_FLAGS(INIT_DEFAULT);

#include <tari/log.h>
#include <tari/pvr.h>
#include <tari/physics.h>

#include "basetypes.h"
#include "game.h"

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

uint32_t useRomDisk = 1;

//Main Function.

#define DEVELOP

int main() {

  initiatePVR();
  initPhysics();

  log("Begin game routine");
  GameReturnType returnType = gameLogic();

  if (returnType == RETURN_TO_MENU) {
#ifdef DEVELOP
    arch_exit();
#else
    arch_menu();
#endif
  }

  return (1);
}
