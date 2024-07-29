#ifndef _CALC_H
#define _CALC_H
#include <raylib.h>
#include <stdint.h>
#include "darray.h"

typedef struct {
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    Vector2 p4;
}Quadrangle;

typedef struct {
    Vector2 pos;
    uint32_t radius; 
    Color color;
}Circle;


Quadrangle rotateQuad(Quadrangle quad, float angle);
Quadrangle texturePosToQuad(Vector2 pos, Texture2D texture);
DArray* generateRandomCircle(int count);

#endif
