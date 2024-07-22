#include "enemy.h"
#include "shot.h"
#include <time.h>
#include <stdio.h>


void fireEnemyBullet(EnemyInfo *info){
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    size_t elapsed_ms = (now.tv_sec - info->lastFire.tv_sec) * 1000 + (now.tv_nsec - info->lastFire.tv_nsec) / 1000000;

    if(elapsed_ms >= info->fireDelay){
        fireBullet(info->shotArray, info->bulletSpeed, *info->shipMove);
        info->lastFire = now;
    }
}
