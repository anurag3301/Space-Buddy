#include "enemy.h"
#include "bullet.h"
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


void bulletHitEnemy(ShipInfo *enemy, ShipInfo ship){
    for(size_t i=0; i<ship.bulletArray->size; i++){
        if(bulletCollision(*(enemy->move), enemy->texture, *(MoveInfo*)ship.bulletArray->data[i])){
            enemy->health -= ship.damage;
            if(enemy->health <= 0); // TODO: add enemy execution
            removeDA(ship.bulletArray, i);
        }
    }
}


void bulletHitPlayer(ShipInfo *ship, ShipInfo enemy){
    for(size_t i=0; i<enemy.bulletArray->size; i++){
        if(bulletCollision(*(ship->move), ship->texture, *(MoveInfo*)enemy.bulletArray->data[i])){
            ship->health -= enemy.damage;
            if(ship->health <= 0); // TODO: add enemy execution
            removeDA(enemy.bulletArray, i);
        }
    }
}
