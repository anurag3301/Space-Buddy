#ifndef _ENEMY_H
#define _ENEMY_H
#include <stddef.h>
#include "moveableElement.h"
#include "darray.h"
#include <time.h>

typedef struct{
    size_t fireDelay;
    struct timespec lastFire;
    MoveInfo *shipMove;
    int bulletSpeed;
    DArray *shotArray;
} EnemyInfo;

void fireEnemyBullet(EnemyInfo* info);

void moveEnemyShip(EnemyInfo *info);

void bulletHitEnemy(EnemyInfo *info, Texture2D enemyTexture, DArray *shotArr, Texture2D shotTexture);

#endif
