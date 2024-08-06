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
uint score = 0;

Texture2D shipTexture, bulletTexture, enemyTexture, enemyBulletTexture ;

int main(){
    InitWindow(screenWidth, screenHeight, "Space Buddy");
    SetTargetFPS(60);

    shipTexture = textureFromImage("images/ship.png");
    bulletTexture = textureFromImage("images/bullet.png");
    enemyTexture = textureFromImage("images/enemy.png");
    enemyBulletTexture = textureFromImage("images/enemybullet.png");

    DArray* bgCircles = generateRandomCircle(100);

    MoveInfo shipMoveInfo = {6, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 
    ShipInfo ship = {0, {0,0}, &shipMoveInfo, 15, createDArray(), shipTexture, 1000, 1000, 100};

    DArray* enemyShips = createDArray();
    createRandomEnemy(enemyShips, enemyTexture, 1);

    while(!WindowShouldClose()){
        if(enemyShips->size == 0){
            createRandomEnemy(enemyShips, enemyTexture, GetRandomValue(1, 3));
        }

        BeginDrawing();
        ClearBackground(BLACK);

        captureMoveInput(ship.move); 
        updateShipPosition(ship);

        moveEnemyShip(enemyShips);

        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            fireBullet(ship.bulletArray, 25, *ship.move); 
        }

        fireEnemyBullet(enemyShips);

        updateBulletPosition(ship.bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
        (*ship.move).angle = angleBW2Vector(shipMoveInfo.pos, (Vector2){GetMouseX(), GetMouseY()});
        for(size_t i=0; i<enemyShips->size; i++){
            ShipInfo *info = enemyShips->data[i];
            updateBulletPosition(info->bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
            (*info->move).angle = angleBW2Vector((*info->move).pos, (*ship.move).pos);
        }
        
        bulletHitEnemy(enemyShips, ship);
        bulletHitPlayer(&ship, enemyShips);


        for(size_t i=0; i<bgCircles->size; i++){
            Circle* circle = (Circle*)bgCircles->data[i];
            DrawCircleV(circle->pos, circle->radius, circle->color);
        }

        drawBullet(ship.bulletArray, bulletTexture);
        for(size_t i=0; i<enemyShips->size; i++)
            drawBullet(((ShipInfo*)enemyShips->data[i])->bulletArray, enemyBulletTexture);

        drawShip(ship);
        for(size_t i=0; i<enemyShips->size; i++)
            drawShip(*(ShipInfo*)enemyShips->data[i]);

        char scoreBuf[10];
        sprintf(scoreBuf, "%d", score);
        DrawText(scoreBuf, 15, 15, 50, RED);

        EndDrawing();
    }

    freeDA(&ship.bulletArray);
    deleteEnemyShips(enemyShips);

    UnloadTexture(shipTexture);
    CloseWindow();
}
