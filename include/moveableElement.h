#ifndef _MOVEABLEELEMENT_H
#define _MOVEABLEELEMENT_H
#include <raylib.h>
#include "main.h"

typedef struct{
    int speed;
    Vector2 pos;
    float angle;
    Direction2D moveDir;
    RotationDirection rotate;
} MoveInfo;


#endif
