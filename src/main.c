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
#include "ship.h"



const int screenWidth = 1600;
const int screenHeight = 900;


int main(){
    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    Texture2D shipTexture = textureFromImage("images/ship.png");
    Texture2D shotTexture = textureFromImage("images/shot.png");
    Texture2D enemyTexture = textureFromImage("images/enemy.png");
    Texture2D enemyShotTexture = textureFromImage("images/enemyshot.png");


    MoveInfo shipMoveInfo = {6, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 
    ShipInfo ship = {0, {0,0}, &shipMoveInfo, 15, createDArray(), shipTexture};

    MoveInfo enemyMoveInfo = {3, {200, 200}, 0, {NONE, NONE}, NOROTATE}; 
    ShipInfo enemy = {400, {0,0}, &enemyMoveInfo, 15, createDArray(), enemyTexture};
    clock_gettime(CLOCK_MONOTONIC, &enemy.lastFire);


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        captureMoveInput(ship.shipMove); 
        updateShipPosition(ship);

        moveEnemyShip(&enemy);

        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            fireBullet(ship.shotArray, 25, *ship.shipMove); 
        }

        fireEnemyBullet(&enemy);

        UpdatePositionShot(ship.shotArray, (Vector2){shotTexture.width, shotTexture.height});
        UpdatePositionShot(enemy.shotArray, (Vector2){shotTexture.width, shotTexture.height});
        
        bulletHitEnemy(&enemy, enemyTexture, ship.shotArray);

        (*ship.shipMove).angle = angleBW2Vector(shipMoveInfo.pos, (Vector2){GetMouseX(), GetMouseY()});
        (*enemy.shipMove).angle = angleBW2Vector((*enemy.shipMove).pos, (*ship.shipMove).pos);

        DrawBullet(ship.shotArray, shotTexture);
        DrawBullet(enemy.shotArray, enemyShotTexture);

        drawShip(ship);
        drawShip(enemy);

        EndDrawing();
    }

    freeDA(&ship.shotArray);
    freeDA(&enemy.shotArray);

    UnloadTexture(shipTexture);
    CloseWindow();
}
