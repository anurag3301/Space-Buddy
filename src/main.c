#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "movement.h"
#include "darray.h"
#include "moveableElement.h"


int main(){
    const int screenWidth = 1600;
    const int screenHeight = 900;

    MoveInfo shipMoveInfo = {5, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 

    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    Image shipImage = LoadImage("images/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);
    UnloadImage(shipImage);

    Image shotImage = LoadImage("images/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);
    UnloadImage(shotImage);

    DArray shotArray = createDArray();

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMovement(&shipMoveInfo); 
        UpdatePosition(&shipMoveInfo, (Vector2){shipTexture.width, shipTexture.height});

        if(IsKeyPressed(KEY_SPACE)){
            MoveInfo temp = {15, {shipMoveInfo.pos.x, shipMoveInfo.pos.y}, shipMoveInfo.angle, {NONE, NONE}, NOROTATE}; 
            MoveInfo* shotMoveInfo = malloc(sizeof(MoveInfo));
            memcpy(shotMoveInfo, &temp, sizeof(MoveInfo)); 
            appendDA(&shotArray, shotMoveInfo); 
        }

        UpdatePositionShot(&shotArray, (Vector2){shotTexture.width, shotTexture.height});

        /* angle = faceMouseAngle(rectPos); */

        for(size_t i=0; i<shotArray.size; i++){
            MoveInfo shotMove = *((MoveInfo*)shotArray.data[i]);
            DrawTexturePro(shotTexture, (Rectangle){0, 0, shotTexture.width, shotTexture.height}, 
                    (Rectangle){shotMove.pos.x, shotMove.pos.y, shotTexture.width, shotTexture.height}, 
                    (Vector2){shotTexture.width / 2.0f, shotTexture.height / 2.0f }, 
                    shotMove.angle, RAYWHITE);
        }

        DrawTexturePro(shipTexture, (Rectangle){0, 0, shipTexture.width, shipTexture.height}, 
                (Rectangle){shipMoveInfo.pos.x, shipMoveInfo.pos.y, shipTexture.width, shipTexture.height}, 
                (Vector2){shipTexture.width / 2.0f, shipTexture.height / 2.0f }, 
                shipMoveInfo.angle, RAYWHITE);
    
        EndDrawing();
    }

    freeDA(&shotArray);

    UnloadTexture(shipTexture);
    CloseWindow();
}
