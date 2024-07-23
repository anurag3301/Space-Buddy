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


void moveEnemyShip(EnemyInfo *info){
    MoveInfo *move = info->shipMove;

    if(move->moveDir.vertical == UP){
        move->pos.y -= move->speed;
    }
    else if(move->moveDir.vertical == DOWN){
        move->pos.y += move->speed;
    }

    if(move->moveDir.horizontal == RIGHT){
        move->pos.x += move->speed;
    }
    else if(move->moveDir.horizontal == LEFT){
        move->pos.x -= move->speed;
    }

    if(move->moveDir.horizontal == NONE) move->moveDir.horizontal = RIGHT;

    if(move->pos.x < 0) move->moveDir.horizontal = RIGHT;

    /* if(move->pos.y-size.y/2 < 0)move->pos.y += move->speed; */
    if(move->pos.x > GetScreenWidth())move->moveDir.horizontal = LEFT;
    /* if(move->pos.y+size.y/2 > GetScreenHeight())move->pos.y -= move->speed; */
}
