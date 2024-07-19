#include <stdio.h>
#include <raylib.h>

#include "main.h"
#include "movement.h"



int main(){
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int speed = 5;

    Vector2 rectPos = {screenWidth/2-50, screenHeight/2-50};
    Direction2D moveDirection = {NONE, NONE};
    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        UpdateMovement(&moveDirection); 
        UpdatePosition(&rectPos, moveDirection, speed);

        DrawRectangleV(rectPos, (Vector2){100, 100}, RED);
        EndDrawing();
    }

    CloseWindow();
}
