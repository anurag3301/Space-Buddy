#include "movement.h"
#include <raylib.h>

void UpdateMovement(Direction2D *moveDirection){
    if(IsKeyPressed(KEY_W) || IsKeyPressedRepeat(KEY_W)){
        moveDirection->vertical = UP;
    }
    if(IsKeyPressed(KEY_S) || IsKeyPressedRepeat(KEY_S)){
        moveDirection->vertical = DOWN;
    }
    if(IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A)){
        moveDirection->horizontal = LEFT;
    }
    if(IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D)){
        moveDirection->horizontal = RIGHT;
    }

    if((IsKeyReleased(KEY_W) && moveDirection->vertical == UP)||
       (IsKeyReleased(KEY_S) && moveDirection->vertical == DOWN)){
        moveDirection->vertical = NONE;
    }

    if((IsKeyReleased(KEY_A) && moveDirection->horizontal == LEFT)||
       (IsKeyReleased(KEY_D) && moveDirection->horizontal == RIGHT)){
        moveDirection->horizontal = NONE;
    }
}


void UpdatePosition(Vector2* pos, Direction2D moveDirection, int speed){
    if(moveDirection.vertical == UP){
        pos->y -= speed;
    }
    else if(moveDirection.vertical == DOWN){
        pos->y += speed;
    }
    if(moveDirection.horizontal == RIGHT){
        pos->x += speed;
    }
    else if(moveDirection.horizontal == LEFT){
        pos->x -= speed;
    }
}
