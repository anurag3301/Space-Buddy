#ifndef _MAIN_H
#define _MAIN_H

typedef enum {NONE, UP, DOWN, RIGHT, LEFT}Direction;
typedef enum {NOROTATE, CLOCKWISE, ANTICLOCKWISE}RotationDirection;

typedef struct{
    Direction horizontal;
    Direction vertical;
} Direction2D;

#endif
