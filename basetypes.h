#ifndef BASETYPES_H
#define BASETYPES_H

#include <stdint.h>

typedef enum {
	RETURN_NORMAL,
	RETURN_TO_MENU,
	RETURN_WON, //TODO: rename to _WIN
	RETURN_LOSS
} GameReturnType;

typedef enum {
	TILE_EMPTY,
	TILE_PLATFORM
} TileType;


typedef struct {
	double x;
	double y;
} Vector2D;

typedef struct {
	int x;
	int y;
} Vector2DI;

typedef double Size1;
typedef Vector2D Position;
typedef Vector2D Velocity;
typedef Vector2D Acceleration;

typedef Vector2DI PositionI;
typedef Vector2DI VelocityI;

typedef Vector2DI TextureSize;

#define TileToRealPositionX(x)			(x*TILE_SIZE)
#define TileToRealPositionY(y)			(y*TILE_SIZE+PLATFORM_SIZE_Y)
#define TileToRealPositionWithoutPlatformY(y)	(y*TILE_SIZE)
#define RealPositionToTileX(x)			(x/TILE_SIZE)
#define RealPositionToTileY(y)			((y-PLATFORM_SIZE_Y)/TILE_SIZE)
#define RealPositionToTileWitoutPlatformY(y)	(y/TILE_SIZE)


typedef uint32_t Frame;
typedef uint32_t AnimationTick;

typedef enum{
	FACE_RIGHT,
	FACE_LEFT
} FaceDirection;

typedef struct{
	Position topLeft;
	Position bottomRight;
} Rectangle;

typedef struct{
	PositionI topLeft;
	PositionI bottomRight;
} RectangleI;

#endif
