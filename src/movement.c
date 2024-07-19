#include "movement.h"
#include "main.h"
#include <raylib.h>
#include <math.h>

void UpdateMovement(Direction2D *moveDirection, RotationDirection *rotate){
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
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)){
        *rotate = CLOCKWISE; 
    }
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)){
        *rotate = ANTICLOCKWISE; 
    }

    if((IsKeyReleased(KEY_W) && moveDirection->vertical == UP)||
       (IsKeyReleased(KEY_S) && moveDirection->vertical == DOWN)){
        moveDirection->vertical = NONE;
    }

    if((IsKeyReleased(KEY_A) && moveDirection->horizontal == LEFT)||
       (IsKeyReleased(KEY_D) && moveDirection->horizontal == RIGHT)){
        moveDirection->horizontal = NONE;
    }

    if((IsKeyReleased(KEY_RIGHT) && *rotate == CLOCKWISE)||
       (IsKeyReleased(KEY_LEFT) && *rotate == ANTICLOCKWISE)){
        *rotate = NOROTATE;
    }
}


void UpdatePosition(Vector2* pos, float* angle, Direction2D moveDirection, RotationDirection rotate, int speed, Vector2 size){
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

    if(pos->x-size.x/2 < 0)pos->x += speed;
    if(pos->y-size.y/2 < 0)pos->y += speed;
    if(pos->x+size.x/2 > GetScreenWidth())pos->x -= speed;
    if(pos->y+size.y/2 > GetScreenHeight())pos->y -= speed;


    if(rotate == CLOCKWISE) *angle += speed*0.5;
    else if(rotate == ANTICLOCKWISE) *angle -= speed*0.5;
}


float faceMouseAngle(Vector2 pos){
    Vector2 diff = {GetMouseX()-pos.x, GetMouseY()-pos.y};
    float rotation = atan2(diff.y, diff.x) * RAD2DEG;
    return rotation;
}
