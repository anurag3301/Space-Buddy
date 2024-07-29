#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "movement.h"
#include "darray.h"
#include "moveableElement.h"
#include "bullet.h"
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
    Texture2D bulletTexture = textureFromImage("images/bullet.png");
    Texture2D enemyTexture = textureFromImage("images/enemy.png");
    Texture2D enemyBulletTexture = textureFromImage("images/enemybullet.png");


    MoveInfo shipMoveInfo = {6, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 
    ShipInfo ship = {0, {0,0}, &shipMoveInfo, 15, createDArray(), shipTexture};

    MoveInfo enemyMoveInfo = {3, {200, 200}, 0, {NONE, NONE}, NOROTATE}; 
    ShipInfo enemy = {400, {0,0}, &enemyMoveInfo, 15, createDArray(), enemyTexture};
    clock_gettime(CLOCK_MONOTONIC, &enemy.lastFire);


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        captureMoveInput(ship.move); 
        updateShipPosition(ship);

        moveEnemyShip(&enemy);

        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            fireBullet(ship.bulletArray, 25, *ship.move); 
        }

        fireEnemyBullet(&enemy);

        updateBulletPosition(ship.bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
        updateBulletPosition(enemy.bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
        
        bulletHitEnemy(&enemy, enemyTexture, ship.bulletArray);

        (*ship.move).angle = angleBW2Vector(shipMoveInfo.pos, (Vector2){GetMouseX(), GetMouseY()});
        (*enemy.move).angle = angleBW2Vector((*enemy.move).pos, (*ship.move).pos);

        drawBullet(ship.bulletArray, bulletTexture);
        drawBullet(enemy.bulletArray, enemyBulletTexture);

        drawShip(ship);
        drawShip(enemy);

        EndDrawing();
    }

    freeDA(&ship.bulletArray);
    freeDA(&enemy.bulletArray);

    UnloadTexture(shipTexture);
    CloseWindow();
}
