#ifndef _ENEMY_H
#define _ENEMY_H
#include <stddef.h>
#include "moveableElement.h"
#include "darray.h"
#include "ship.h"
#include <sys/types.h>

void fireEnemyBullet(DArray* ships);
void moveEnemyShip(DArray* ships);
void bulletHitEnemy(DArray* enemyShips, ShipInfo ship);
void bulletHitPlayer(ShipInfo *ship, DArray* enemyShips);
void createRandomEnemy(DArray* arr, Texture2D enemyTexture, uint count);
void deleteEnemyShips(DArray* enemyShips);

#endif
