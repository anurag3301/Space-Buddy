#include "movement.h"
#include "main.h"
#include "moveableElement.h"
#include <raylib.h>
#include <math.h>
#include <raymath.h>

void captureMoveInput(MoveInfo *move){
    if(IsKeyPressed(KEY_W) || IsKeyPressedRepeat(KEY_W)){
        move->moveDir.vertical = UP;
    }
    if(IsKeyPressed(KEY_S) || IsKeyPressedRepeat(KEY_S)){
        move->moveDir.vertical = DOWN;
    }
    if(IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A)){
        move->moveDir.horizontal = LEFT;
    }
    if(IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D)){
        move->moveDir.horizontal = RIGHT;
    }
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)){
        move->rotate = CLOCKWISE; 
    }
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)){
        move->rotate = ANTICLOCKWISE; 
    }

    if((IsKeyReleased(KEY_W) && move->moveDir.vertical == UP)||
       (IsKeyReleased(KEY_S) && move->moveDir.vertical == DOWN)){
        move->moveDir.vertical = NONE;
    }

    if((IsKeyReleased(KEY_A) && move->moveDir.horizontal == LEFT)||
       (IsKeyReleased(KEY_D) && move->moveDir.horizontal == RIGHT)){
        move->moveDir.horizontal = NONE;
    }

    if((IsKeyReleased(KEY_RIGHT) && move->rotate == CLOCKWISE)||
       (IsKeyReleased(KEY_LEFT) && move->rotate == ANTICLOCKWISE)){
        move->rotate = NOROTATE;
    }
}




float angleBW2Vector(Vector2 pos, Vector2 targetPos){
    Vector2 diff = Vector2Subtract(targetPos, pos);
    float rotation = atan2(diff.y, diff.x) * RAD2DEG;
    return rotation;
}


