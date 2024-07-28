#ifndef _BULLET_H
#define _BULLET_H
#include "darray.h"
#include "moveableElement.h"

void updateBulletPosition(DArray *bulletArr, Vector2 size);
void fireBullet(DArray *bulletArray, int speed, MoveInfo shipMoveInfo);
void drawBullet(DArray *bulletArray, Texture2D bulletTexture);
bool bulletCollision(MoveInfo shipMove, Texture2D shipTexture, MoveInfo bulletMove);

#endif
