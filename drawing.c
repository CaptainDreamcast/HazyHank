#include "drawing.h"

#include <kos.h>
#include <dc/matrix3d.h>
#include <stdlib.h>

#include "texture.h"

#include "log.h"

#define M_PI 3.14159

double inverseScreenY(double y){
	return (SCREEN_SIZE_Y-y);
}

void applyDrawingMatrixSingle(float* tX, float* tY, float* tZ, float tTiltAngle){
	float dx1 = MIDDLE_OF_SCREEN_X;
	float dy1 = MIDDLE_OF_SCREEN_Y;
	float dz1 = 0;

	float dx2 = -MIDDLE_OF_SCREEN_X;
	float dy2 = -MIDDLE_OF_SCREEN_Y;
	float dz2 = 0;

	mat_identity();
	mat_translate(dx1, dy1, dz1);
	mat_rotate_z(tTiltAngle);
	mat_translate(dx2, dy2, dz2);
	mat_trans_single((*tX), (*tY), (*tZ));
}

void applyDrawingMatrix(pvr_vertex_t* tVert, double tTiltAngle){
	applyDrawingMatrixSingle(&tVert->x, &tVert->y, &tVert->z, tTiltAngle);
}

// TODO: find out why sprite drawing does not work
void drawSprite(pvr_ptr_t tTexture, Position tPos, int tZ, Vector2DI tTextureSize, RectangleI tTexturePosition, double tTiltAngle){

	debugLog("Draw Sprite");
	debugInteger(tTextureSize.x);
	debugInteger(tTextureSize.y);

	if(tTextureSize.x < 0 || tTextureSize.y < 0 || tTextureSize.x % 2 != 0 || tTextureSize.y % 2 != 0){
		logInteger(tTextureSize.x);
		logInteger(tTextureSize.y);
		log("Leaving function")
		return;
	}

	int sizeX = tTexturePosition.bottomRight.x-tTexturePosition.topLeft.x;
	int sizeY = tTexturePosition.topLeft.y-tTexturePosition.bottomRight.y;

	debugInteger(tTexturePosition.bottomRight.x);
	debugInteger(tTexturePosition.topLeft.x);
	debugInteger(sizeX);

	double left, right;
	if(tTexturePosition.bottomRight.x < tTexturePosition.topLeft.x){
		sizeX = -sizeX;
		left = 1.0;
		right = 0.0;
	} else {
		left = 0.0;
		right = 1.0;
	}

	pvr_poly_cxt_t cxt;
	pvr_poly_hdr_t hdr;
	pvr_vertex_t vert;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, tTextureSize.x, tTextureSize.y, tTexture, PVR_FILTER_BILINEAR);

	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vert.oargb = 0;
	vert.flags = PVR_CMD_VERTEX;

	vert.x = tPos.x;
	vert.y = inverseScreenY(tPos.y-sizeY);
	vert.z = tZ;
	vert.u = left;
	vert.v = 0;
	applyDrawingMatrix(&vert, tTiltAngle);
	vert.z = tZ;
	pvr_prim(&vert, sizeof(vert));

	vert.x = tPos.x+sizeX;
	vert.y = inverseScreenY(tPos.y-sizeY);
	vert.z = tZ;
	vert.u = right;
	vert.v = 0;
	applyDrawingMatrix(&vert, tTiltAngle);
	vert.z = tZ;
	pvr_prim(&vert, sizeof(vert));

	vert.x = tPos.x;
	vert.y = inverseScreenY(tPos.y);
	vert.z = tZ;
	vert.u = left;
	vert.v = 1;
	applyDrawingMatrix(&vert, tTiltAngle);
	vert.z = tZ;
	pvr_prim(&vert, sizeof(vert));

	vert.x = tPos.x+sizeX;
	vert.y = inverseScreenY(tPos.y);
	vert.z = tZ;
	vert.u = right;
	vert.v = 1;
	vert.flags = PVR_CMD_VERTEX_EOL;
	applyDrawingMatrix(&vert, tTiltAngle);
	vert.z = tZ;
	pvr_prim(&vert, sizeof(vert));
}

void startDrawing(){
	pvr_scene_begin();
   	pvr_list_begin(PVR_LIST_TR_POLY);
}

void stopDrawing(){
	pvr_list_finish();
    	pvr_scene_finish();
}

void drawCharacter(WorldData* tWorldData, CharacterData* tCharacterData){
	debugLog("Draw character");	
	TextureData textureData = getCharacterTexture(tCharacterData->frame);
	FaceDirection faceDirection = tCharacterData->faceDirection;

	RectangleI tTexturePosition;
	tTexturePosition.topLeft.x = (faceDirection == FACE_RIGHT) ? 0 : (textureData.textureSize.x-1);
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = (faceDirection != FACE_RIGHT) ? 0 : (textureData.textureSize.x-1);
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	if(textureData.textureSize.x < 0 || textureData.textureSize.y < 0){
		logInteger(textureData.textureSize.x);
		logInteger(textureData.textureSize.y);
	}

	drawSprite(textureData.texture, tCharacterData->position, CHARACTER_POSITION_Z, textureData.textureSize, tTexturePosition, tWorldData->tiltAngle);
}

void drawEnemies(WorldData* tWorldData){	
	debugLog("Draw enemies");

	int i;
	for(i = 0; i < tWorldData->enemyAmount; i++){
		FaceDirection faceDirection = tWorldData->enemies[i].faceDirection;
		TextureData textureData = getEnemyTexture(tWorldData->enemies[i].frame);

		RectangleI tTexturePosition;
		tTexturePosition.topLeft.x = (faceDirection == FACE_RIGHT) ? 0 : (textureData.textureSize.x-1);
		tTexturePosition.topLeft.y = 0;
		tTexturePosition.bottomRight.x = (faceDirection != FACE_RIGHT) ? 0 : (textureData.textureSize.x-1);
		tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

		if(textureData.textureSize.x < 0 || textureData.textureSize.y < 0){
			logInteger(textureData.textureSize.x);
			logInteger(textureData.textureSize.y);
		}


		drawSprite(textureData.texture, tWorldData->enemies[i].position, ENEMY_POSITION_Z, textureData.textureSize, tTexturePosition, tWorldData->tiltAngle);
	}
}

void drawBackground(WorldData* tWorldData){	
	debugLog("Draw background");

	TextureData textureData = getBackgroundTexture();
	RectangleI tTexturePosition;
	
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.textureSize.x-1;
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	Position position;
	position.x = 0;
	position.y = 0;

	if(textureData.textureSize.x < 0 || textureData.textureSize.y < 0){
		logInteger(textureData.textureSize.x);
		logInteger(textureData.textureSize.y);
	}

	drawSprite(textureData.texture, position, BACKGROUND_POSITION_Z, textureData.textureSize, tTexturePosition, tWorldData->tiltAngle);
}

void drawPlatforms(WorldData* tWorldData){	
	debugLog("Draw platforms");

	TextureData textureData = getPlatformTexture();

	RectangleI tTexturePosition;
	
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.textureSize.x-1;
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	int i, j;
	for(j = 0; j < MAX_TILES_Y; j++){
		for(i = 0; i < MAX_TILES_X; i++){
			
			if(tWorldData->tiles[j][i] == TILE_PLATFORM){
				debugLog("Draw single tile");
				debugInteger(i);
				debugInteger(j);
				Position position;
				position.x = TileToRealPositionX(i);
				position.y = TileToRealPositionWithoutPlatformY(j);

				if(textureData.textureSize.x < 0 || textureData.textureSize.y < 0){
					logInteger(textureData.textureSize.x);
					logInteger(textureData.textureSize.y);
				}

				drawSprite(textureData.texture, position, PLATFORM_POSITION_Z, textureData.textureSize, tTexturePosition, tWorldData->tiltAngle);
			}
		}
	}
}


void drawExit(WorldData* tWorldData){
	debugLog("Draw Exit");
	
	TextureData textureData = getExitTexture();

	RectangleI tTexturePosition;
	
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.textureSize.x-1;
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	if(textureData.textureSize.x < 0 || textureData.textureSize.y < 0){
		logInteger(textureData.textureSize.x);
		logInteger(textureData.textureSize.y);
	}

	drawSprite(textureData.texture, tWorldData->exitPosition, EXIT_POSITION_Z, textureData.textureSize, tTexturePosition, tWorldData->tiltAngle);
}

void draw(WorldData* tWorldData, CharacterData* tCharacterData){
	debugLog("Begin drawing");
	startDrawing();
	drawBackground(tWorldData);
	drawPlatforms(tWorldData);
	drawCharacter(tWorldData, tCharacterData);
	drawEnemies(tWorldData);
	drawExit(tWorldData);
	stopDrawing();
}

void drawTitleBackground(TitleData* tTitleData){
	debugLog("Draw Title background");
	
	TextureData textureData = getTitleTexture();

	RectangleI tTexturePosition;
	
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.textureSize.x-1;
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	Position pos;
	pos.x = 0;
	pos.y = 0;

	drawSprite(textureData.texture, pos, BACKGROUND_POSITION_Z, textureData.textureSize, tTexturePosition, tTitleData->tiltAngle);
}

void drawPressStart(TitleData* tTitleData){
	debugLog("Draw Title background");
	
	TextureData textureData = getPressStartTexture();

	RectangleI tTexturePosition;
	
	tTexturePosition.topLeft.x = 0;
	tTexturePosition.topLeft.y = 0;
	tTexturePosition.bottomRight.x = textureData.textureSize.x-1;
	tTexturePosition.bottomRight.y = textureData.textureSize.y-1;

	Position pos;
	pos.x = PRESS_START_X;
	pos.y = PRESS_START_Y;

	drawSprite(textureData.texture, pos, CHARACTER_POSITION_Z, textureData.textureSize, tTexturePosition, tTitleData->tiltAngle);
}

void drawTitle(TitleData* tTitleData){
	debugLog("Begin drawing title");
	startDrawing();
	drawTitleBackground(tTitleData);
	drawPressStart(tTitleData);
	stopDrawing();
}

void waitForScreen(){
	debugLog("Wait for screen");	
	pvr_wait_ready();
	debugLog("Wait for screen done");
}


void getRGBFromColor(Color tColor, double* tR, double* tG, double* tB){
	if(tColor == COLOR_BLACK) { 
		(*tR) = (*tG) = (*tB) = 0;
	}
	else if(tColor == COLOR_RED){ 
		(*tR) = 1.0f; 
		(*tG) = (*tB) = 0;}
	else if(tColor == COLOR_GREEN){ 
		(*tG) = 1.0f; 
		(*tR) = (*tB) = 0;
	}
	else if(tColor == COLOR_BLUE){ 
		(*tB) = 1.0f; 
		(*tG) = (*tR) = 0;
	}
	else if(tColor == COLOR_YELLOW){ 
		(*tG) = (*tR) = 1.0f; 
		(*tB) = 0;
	}
	else { 
		(*tR) = (*tG) = (*tB) = 1.0f;
	}
}


void drawText(char tText[], Position tPosition, int tZ, int tSize, Color tColor){

	pvr_poly_cxt_t cxt;
	pvr_poly_hdr_t hdr;
	pvr_vertex_t vert;

	int current = 0;

	double r, g, b;
	getRGBFromColor(tColor, &r, &g, &b);

	TextureData fontData = getFontTexture();
	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, fontData.textureSize.x, fontData.textureSize.y, fontData.texture, PVR_FILTER_BILINEAR);

	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	while(tText[current] != '\0'){

		FontCharacterData charData = getFontCharacterData(tText[current]);

		vert.argb = PVR_PACK_COLOR(1.0f, r, g, b);
		vert.oargb = 0;
		vert.flags = PVR_CMD_VERTEX;		

		vert.x = tPosition.x;
		vert.y = tPosition.y;
		vert.z = tZ;
		vert.u = charData.filePositionX1;
		vert.v = charData.filePositionY1;
		pvr_prim(&vert, sizeof(vert));

		vert.x = tPosition.x+tSize;
		vert.y = tPosition.y;
		vert.z = tZ;
		vert.u = charData.filePositionX2;
		vert.v = charData.filePositionY1;
		pvr_prim(&vert, sizeof(vert));

		vert.x = tPosition.x;
		vert.y = tPosition.y+tSize;
		vert.z = tZ;
		vert.u = charData.filePositionX1;
		vert.v = charData.filePositionY2;
		pvr_prim(&vert, sizeof(vert));

		vert.x = tPosition.x+tSize;
		vert.y = tPosition.y+tSize;
		vert.z = tZ;
		vert.u = charData.filePositionX2;
		vert.v = charData.filePositionY2;
		vert.flags = PVR_CMD_VERTEX_EOL;
		pvr_prim(&vert, sizeof(vert));

		tPosition.x+=tSize;
		current++;
	}

}

