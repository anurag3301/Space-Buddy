#include "enemy.h"
#include "shot.h"
#include <time.h>
#include <stdio.h>


void fireEnemyBullet(ShipInfo *info){
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    size_t elapsed_ms = (now.tv_sec - info->lastFire.tv_sec) * 1000 + (now.tv_nsec - info->lastFire.tv_nsec) / 1000000;

    if(elapsed_ms >= info->fireDelay){
        fireBullet(info->bulletArray, info->bulletSpeed, *info->move);
        info->lastFire = now;
    }
}


void moveEnemyShip(ShipInfo *info){
    MoveInfo *move = info->move;

    if(move->direction.vertical == UP){
        move->pos.y -= move->speed;
    }
    else if(move->direction.vertical == DOWN){
        move->pos.y += move->speed;
    }

    if(move->direction.horizontal == RIGHT){
        move->pos.x += move->speed;
    }
    else if(move->direction.horizontal == LEFT){
        move->pos.x -= move->speed;
    }

    if(move->direction.horizontal == NONE) move->direction.horizontal = RIGHT;

    if(move->pos.x < 0) move->direction.horizontal = RIGHT;

    /* if(move->pos.y-size.y/2 < 0)move->pos.y += move->speed; */
    if(move->pos.x > GetScreenWidth())move->direction.horizontal = LEFT;
    /* if(move->pos.y+size.y/2 > GetScreenHeight())move->pos.y -= move->speed; */
}


void bulletHitEnemy(ShipInfo *info, Texture2D enemyTexture, DArray *shotArr){
    for(size_t i=0; i<shotArr->size; i++){
            removeDA(shotArr, i);
        if(bulletCollision(*(info->move), enemyTexture, *(MoveInfo*)bulletArr->data[i])){
        }
    }
}
