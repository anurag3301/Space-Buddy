#include "enemy.h"
#include "bullet.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fireEnemyBullet(DArray* ships){
    for(size_t i=0; i<ships->size; i++){
        ShipInfo *info = ships->data[i];
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        size_t elapsed_ms = (now.tv_sec - info->lastFire.tv_sec) * 1000 + (now.tv_nsec - info->lastFire.tv_nsec) / 1000000;

        if(elapsed_ms >= info->fireDelay){
            fireBullet(info->bulletArray, info->bulletSpeed, *info->move);
            info->lastFire = now;
        }
    }
}


void createRandomEnemy(DArray* arr, Texture2D enemyTexture, uint count){
    while(count--){
        float x = ((float)rand() / RAND_MAX) * GetScreenWidth();
        float y = ((float)rand() / RAND_MAX) * GetScreenHeight();
        MoveInfo tempMove = {3, {x, y}, 0, {NONE, NONE}, NOROTATE}; 
        MoveInfo* enemyMoveInfo = malloc(sizeof(MoveInfo));
        memcpy(enemyMoveInfo, &tempMove, sizeof(MoveInfo));

        ShipInfo tempEnemy = {400, {0,0}, enemyMoveInfo, 15, createDArray(), 
                            enemyTexture, 1000, 1000, 50};
        clock_gettime(CLOCK_MONOTONIC, &tempEnemy.lastFire);
        ShipInfo* enemy = malloc(sizeof(ShipInfo));
        memcpy(enemy, &tempEnemy, sizeof(ShipInfo));
        appendDA(arr, enemy);
    }
}



void moveEnemyShip(DArray* ships){
    for(size_t i=0; i<ships->size; i++){
        ShipInfo *info = ships->data[i];
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
}


void bulletHitEnemy(DArray* enemyShips, ShipInfo ship){
    for(size_t i=0; i<enemyShips->size; i++){
        ShipInfo *enemy= enemyShips->data[i];
        for(size_t j=0; j<ship.bulletArray->size; j++){
            if(bulletCollision(*(enemy->move), enemy->texture, *(MoveInfo*)ship.bulletArray->data[j])){
                enemy->health -= ship.damage;
                if(enemy->health <= 0){
                    freeDA(&enemy->bulletArray);
                    removeDA(enemyShips, i); // TODO: add enemy execution
                }
                removeDA(ship.bulletArray, j);
            }
        }
    }
}


void bulletHitPlayer(ShipInfo *ship, DArray* enemyShips){
    for(size_t i=0; i<enemyShips->size; i++){
        ShipInfo enemy= *(ShipInfo*)enemyShips->data[i];
        for(size_t j=0; j<enemy.bulletArray->size; j++){
            if(bulletCollision(*(ship->move), ship->texture, *(MoveInfo*)enemy.bulletArray->data[j])){
                ship->health -= enemy.damage;
                if(ship->health <= 0); // TODO: add enemy execution
                removeDA(enemy.bulletArray, j);
            }
        }
    }
}
