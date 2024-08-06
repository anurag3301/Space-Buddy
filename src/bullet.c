#include "bullet.h"
#include "darray.h"
#include "movement.h"
#include "calc.h"
#include "ship.h"
#include <stdlib.h>
#include <string.h>

void fireBullet(DArray *bulletArray, int speed, MoveInfo shipMoveInfo){
        MoveInfo temp = {speed, {shipMoveInfo.pos.x, shipMoveInfo.pos.y}, shipMoveInfo.angle, {NONE, NONE}, NOROTATE}; 
        MoveInfo* bulletMoveInfo = malloc(sizeof(MoveInfo));
        memcpy(bulletMoveInfo, &temp, sizeof(MoveInfo)); 
        appendDA(bulletArray, bulletMoveInfo); 
}

void drawBullet(DArray *bulletArray, Texture2D bulletTexture){
    for(size_t i=0; i<bulletArray->size; i++){
        MoveInfo bulletMove = *((MoveInfo*)bulletArray->data[i]);
        DrawTexturePro(bulletTexture, (Rectangle){0, 0, bulletTexture.width, bulletTexture.height}, 
                (Rectangle){bulletMove.pos.x, bulletMove.pos.y, bulletTexture.width, bulletTexture.height}, 
                (Vector2){bulletTexture.width / 2.0f, bulletTexture.height / 2.0f }, 
                bulletMove.angle, RAYWHITE);
    }
}

bool bulletCollision(MoveInfo shipMove, Texture2D shipTexture, MoveInfo bulletMove){
    Quadrangle shipQuad  = texturePosToQuad(shipMove.pos, shipTexture);
    shipQuad = rotateQuad(shipQuad, DEG2RAD*shipMove.angle);
    Vector2 points[] = {shipQuad.p1, shipQuad.p2, shipQuad.p3, shipQuad.p4};
    return CheckCollisionPointPoly(bulletMove.pos, points, 4);
}

void deleteEnemyShips(DArray* enemyShips){
    for(size_t i=0; i<enemyShips->size; i++){
        ShipInfo* enemy = enemyShips->data[i];
        freeDA(&enemy->bulletArray);
    }
    freeDA(&enemyShips);
}
