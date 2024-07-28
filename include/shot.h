#ifndef _SHOT_H
#define _SHOT_H
#include "darray.h"
#include "moveableElement.h"

void updateShotPosition(DArray *shotArr, Vector2 size);
void fireBullet(DArray *shotArray, int speed, MoveInfo shipMoveInfo);
void drawBullet(DArray *shotArray, Texture2D shotTexture);
bool bulletCollision(MoveInfo shipMove, Texture2D shipTexture, MoveInfo shotMove);

#endif
