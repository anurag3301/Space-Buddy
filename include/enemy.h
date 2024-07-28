#ifndef _ENEMY_H
#define _ENEMY_H
#include <stddef.h>
#include "moveableElement.h"
#include "darray.h"
#include <time.h>
#include "ship.h"

void fireEnemyBullet(ShipInfo* info);

void moveEnemyShip(ShipInfo *info);

void bulletHitEnemy(ShipInfo *info, Texture2D enemyTexture, DArray *shotArr, Texture2D shotTexture);

#endif
