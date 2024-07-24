#ifndef _CALC_H
#define _CALC_H
#include <raylib.h>

typedef struct {
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    Vector2 p4;
}Quadrangle;


Quadrangle rotateQuad(Quadrangle quad, float angle);
Quadrangle texturePosToQuad(Vector2 pos, Texture2D texture);

#endif
