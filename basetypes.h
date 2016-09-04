#ifndef BASETYPES_H
#define BASETYPES_H

#include <stdint.h>

typedef enum {
  RETURN_NORMAL,
  RETURN_TO_MENU,
  RETURN_WON,  //TODO: rename to _WIN
  RETURN_LOSS
} GameReturnType;

typedef enum {
  FACE_RIGHT,
  FACE_LEFT
} FaceDirection;

typedef struct {
  int x;
  int y;
} TilePosition;

#endif
