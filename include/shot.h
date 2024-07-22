#ifndef _SHOT_H
#define _SHOT_H
#include "darray.h"
#include "moveableElement.h"

void fireBullet(DArray *shotArray, int speed, MoveInfo shipMoveInfo);
void DrawBullet(DArray *shotArray, Texture2D shotTexture);

#endif
