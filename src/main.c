#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#include "main.h"
#include "movement.h"


int main(){
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int speed = 5;
    Vector2 rectPos = {screenWidth/2, screenHeight/2};
    float angle = 0;
    Direction2D moveDirection = {NONE, NONE};
    RotationDirection rotate = NOROTATE;

    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    Image shipImage = LoadImage("images/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);
    UnloadImage(shipImage);


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMovement(&moveDirection, &rotate); 
        UpdatePosition(&rectPos, &angle, moveDirection, rotate, speed, 
                        (Vector2){shipTexture.width, shipTexture.height});

        /* angle = faceMouseAngle(rectPos); */

        DrawTexturePro(shipTexture, (Rectangle){0, 0, shipTexture.width, shipTexture.height}, 
                (Rectangle){rectPos.x, rectPos.y, shipTexture.width, shipTexture.height}, 
                (Vector2){shipTexture.width / 2.0f, shipTexture.height / 2.0f }, 
                angle, RAYWHITE);

    
        EndDrawing();
    }

    CloseWindow();
}
