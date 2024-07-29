#ifndef _ENEMY_H
#define _ENEMY_H
#include <stddef.h>
#include "moveableElement.h"
#include "darray.h"
#include "ship.h"

void fireEnemyBullet(ShipInfo* info);
void moveEnemyShip(ShipInfo *info);
void bulletHitEnemy(ShipInfo *enemy, ShipInfo ship);
void bulletHitPlayer(ShipInfo *ship, ShipInfo enemy);

#endif
