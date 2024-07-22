#include "shot.h"
#include "darray.h"
#include "movement.h"
#include <stdlib.h>
#include <string.h>

void fireBullet(DArray *shotArray, int speed, MoveInfo shipMoveInfo){
        MoveInfo temp = {speed, {shipMoveInfo.pos.x, shipMoveInfo.pos.y}, shipMoveInfo.angle, {NONE, NONE}, NOROTATE}; 
        MoveInfo* shotMoveInfo = malloc(sizeof(MoveInfo));
        memcpy(shotMoveInfo, &temp, sizeof(MoveInfo)); 
        appendDA(shotArray, shotMoveInfo); 
}

void DrawBullet(DArray *shotArray, Texture2D shotTexture){
    for(size_t i=0; i<shotArray->size; i++){
        MoveInfo shotMove = *((MoveInfo*)shotArray->data[i]);
        DrawTexturePro(shotTexture, (Rectangle){0, 0, shotTexture.width, shotTexture.height}, 
                (Rectangle){shotMove.pos.x, shotMove.pos.y, shotTexture.width, shotTexture.height}, 
                (Vector2){shotTexture.width / 2.0f, shotTexture.height / 2.0f }, 
                shotMove.angle, RAYWHITE);
    }
}
