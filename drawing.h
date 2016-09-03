#ifndef DRAWING_H
#define DRAWING_H

#include "worlddata.h"
#include "characterdata.h"
#include "titledata.h"

typedef enum{
	COLOR_BLACK,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_YELLOW,
	COLOR_WHITE
} Color;

void draw(WorldData* tWorldData, CharacterData* tCharacterData);
void drawTitle(TitleData* tTitleData);
void waitForScreen();
void drawText(char tText[], Position tPosition, int tZ, int tSize, Color tColor);

#endif
