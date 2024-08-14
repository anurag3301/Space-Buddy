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
uint maxscore = 0;

Texture2D shipTexture, bulletTexture, enemyTexture, enemyBulletTexture ;
Sound enemyBulletSound, shipBulletSound, bullet_hit, blastSound;

int main(){
    InitWindow(screenWidth, screenHeight, "Space Buddy");
    InitAudioDevice();
    SetTargetFPS(60);
    /* SetMasterVolume(0); */

    shipTexture = textureFromImage("images/ship.png");
    bulletTexture = textureFromImage("images/bullet.png");
    enemyTexture = textureFromImage("images/enemy.png");
    enemyBulletTexture = textureFromImage("images/enemybullet.png");
    enemyBulletSound = LoadSound("sound/bullet1.ogg");
    SetSoundVolume(enemyBulletSound, 0.25);
    SetSoundPitch(enemyBulletSound, 0.8);
    shipBulletSound = LoadSound("sound/bullet2.ogg");
    bullet_hit = LoadSound("sound/bullet_hit.ogg");
    SetSoundVolume(bullet_hit, 0.50);
    blastSound = LoadSound("sound/blast.ogg");

    while(!WindowShouldClose()){
        DArray* bgCircles = generateRandomCircle(100);

        MoveInfo shipMoveInfo = {6, {screenWidth/2, screenHeight/2}, 0, {NONE, NONE}, NOROTATE}; 
        ShipInfo ship = {0, {0,0}, &shipMoveInfo, 15, createDArray(), shipTexture, 1000, 1000, 200};

        DArray* enemyShips = createDArray();
        createRandomEnemy(enemyShips, enemyTexture, 1);

        bool gameOver = false;
        char buf[100];
        score = 0;

        while (!WindowShouldClose()) {
            if (!gameOver) {
                if (enemyShips->size == 0) {
                    createRandomEnemy(enemyShips, enemyTexture, GetRandomValue(1, 3));
                }

                captureMoveInput(ship.move);
                updateShipPosition(ship);
                moveEnemyShip(enemyShips);

                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    StopSound(shipBulletSound);
                    PlaySound(shipBulletSound);
                    fireBullet(ship.bulletArray, 25, *ship.move);
                }

                fireEnemyBullet(enemyShips);

                updateBulletPosition(ship.bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
                (*ship.move).angle = angleBW2Vector(shipMoveInfo.pos, (Vector2){GetMouseX(), GetMouseY()});
                for (size_t i = 0; i < enemyShips->size; i++) {
                    ShipInfo *info = enemyShips->data[i];
                    updateBulletPosition(info->bulletArray, (Vector2){bulletTexture.width, bulletTexture.height});
                    (*info->move).angle = angleBW2Vector((*info->move).pos, (*ship.move).pos);
                }

                bulletHitEnemy(enemyShips, ship);
                bulletHitPlayer(&ship, enemyShips);

                for (size_t i = 0; i < bgCircles->size; i++) {
                    Circle* circle = (Circle*)bgCircles->data[i];
                    DrawCircleV(circle->pos, circle->radius, circle->color);
                }

                drawBullet(ship.bulletArray, bulletTexture);
                for (size_t i = 0; i < enemyShips->size; i++) {
                    drawBullet(((ShipInfo*)enemyShips->data[i])->bulletArray, enemyBulletTexture);
                }

                drawShip(ship);
                for (size_t i = 0; i < enemyShips->size; i++) {
                    drawShip(*(ShipInfo*)enemyShips->data[i]);
                }

                sprintf(buf, "%d", score);
                DrawText(buf, 15, 15, 50, RED);

                if (ship.health <= 0) {
                    gameOver = true;
                    maxscore = maxscore > score ? maxscore : score;
                }
            }

            BeginDrawing();
            ClearBackground(BLACK);

            if (gameOver) {
                DrawText("GAME OVER", 200, 200, 200, RED);
                DrawText("Press Enter to retry!!", 200, 400, 100, RED);
                sprintf(buf, "Score: %d", score);
                DrawText(buf, 300, 600, 70, RED);
                sprintf(buf, "Max Score: %d", maxscore);
                DrawText(buf, 800, 600, 70, RED);

                if (IsKeyPressed(KEY_ENTER)) {
                    break;
                }
            }

            EndDrawing();
        }

        freeDA(&ship.bulletArray);
        deleteEnemyShips(enemyShips);
    }

    UnloadTexture(shipTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(enemyBulletTexture);
    UnloadSound(enemyBulletSound);
    UnloadSound(shipBulletSound);
    UnloadSound(bullet_hit);
    UnloadSound(blastSound);
    CloseWindow();
}
