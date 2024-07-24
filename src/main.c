#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "movement.h"
#include "darray.h"
#include "moveableElement.h"
#include "shot.h"
#include "enemy.h"
#include "calc.h"
#include "utils.h"


int main(){
    const int screenWidth = 1600;
    const int screenHeight = 900;

    MoveInfo shipMoveInfo = {6, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 
    MoveInfo enemyMoveInfo = {3, {200, 200}, 0, {NONE, NONE}, NOROTATE}; 
    EnemyInfo enemy = {300, {0,0}, &enemyMoveInfo, 25, createDArray()};
    clock_gettime(CLOCK_MONOTONIC, &enemy.lastFire);

    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    Image shipImage = LoadImage("images/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);
    UnloadImage(shipImage);

    Image shotImage = LoadImage("images/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);
    UnloadImage(shotImage);

    Image enemyImage = LoadImage("images/enemy.png");
    Texture2D enemyTexture = LoadTextureFromImage(enemyImage);
    UnloadImage(enemyImage);

    DArray *shotArray = createDArray();

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMovement(&shipMoveInfo); 
        UpdatePosition(&shipMoveInfo, (Vector2){shipTexture.width, shipTexture.height});
        /* moveEnemyShip(&enemy); */

        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            fireBullet(shotArray, 30, shipMoveInfo); 
        }

        /* fireEnemyBullet(&enemy); */

        UpdatePositionShot(shotArray, (Vector2){shotTexture.width, shotTexture.height});
        UpdatePositionShot(enemy.shotArray, (Vector2){shotTexture.width, shotTexture.height});
        
        bulletHitEnemy(&enemy, enemyTexture, shotArray, enemyTexture);

        shipMoveInfo.angle = angleBW2Vector(shipMoveInfo.pos, (Vector2){GetMouseX(), GetMouseY()});
        enemyMoveInfo.angle = angleBW2Vector(enemyMoveInfo.pos, shipMoveInfo.pos);

        DrawBullet(shotArray, shotTexture);
        DrawBullet(enemy.shotArray, shotTexture);

        DrawTexturePro(shipTexture, (Rectangle){0, 0, shipTexture.width, shipTexture.height}, 
                (Rectangle){shipMoveInfo.pos.x, shipMoveInfo.pos.y, shipTexture.width, shipTexture.height}, 
                (Vector2){shipTexture.width / 2.0f, shipTexture.height / 2.0f }, 
                shipMoveInfo.angle, RAYWHITE);

        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                (Rectangle){enemyMoveInfo.pos.x, enemyMoveInfo.pos.y, enemyTexture.width, enemyTexture.height}, 
                (Vector2){enemyTexture.width / 2.0f, enemyTexture.height / 2.0f }, 
                enemyMoveInfo.angle, RAYWHITE);

        EndDrawing();
    }

    freeDA(&shotArray);
    freeDA(&enemy.shotArray);

    UnloadTexture(shipTexture);
    CloseWindow();
}
