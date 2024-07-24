#ifndef _SHOT_H
#define _SHOT_H
#include "darray.h"
#include "moveableElement.h"

void fireBullet(DArray *shotArray, int speed, MoveInfo shipMoveInfo);
void DrawBullet(DArray *shotArray, Texture2D shotTexture);
bool BulletCollision(MoveInfo shipMove, Texture2D shipTexture, MoveInfo shotMove, Texture2D shotTexture);

#endif
