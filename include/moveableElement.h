#ifndef _MOVEABLEELEMENT_H
#define _MOVEABLEELEMENT_H
#include <raylib.h>

typedef enum {NONE, UP, DOWN, RIGHT, LEFT}Direction;
typedef enum {NOROTATE, CLOCKWISE, ANTICLOCKWISE}RotationDirection;

typedef struct{
    Direction horizontal;
    Direction vertical;
} Direction2D;


typedef struct{
    int speed;
    Vector2 pos;
    float angle;
    Direction2D direction;
    RotationDirection rotate;
} MoveInfo;


#endif
