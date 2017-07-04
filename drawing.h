#ifndef DRAWING_H
#define DRAWING_H

#include "worlddata.h"
#include "characterdata.h"
#include "titledata.h"

void draw(WorldData* tWorldData, CharacterData* tCharacterData);
void updateTiltingMatrix(double tTiltAngle);

#endif

