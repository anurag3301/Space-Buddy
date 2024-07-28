#include "ship.h"
#include <math.h>


void updateShipPosition(ShipInfo ship){
    if(ship.move->direction.vertical == UP){
        ship.move->pos.y -= ship.move->speed;
    }
    else if(ship.move->direction.vertical == DOWN){
        ship.move->pos.y += ship.move->speed;
    }

    if(ship.move->direction.horizontal == RIGHT){
        ship.move->pos.x += ship.move->speed;
    }
    else if(ship.move->direction.horizontal == LEFT){
        ship.move->pos.x -= ship.move->speed;
    }

    if(ship.move->pos.x-ship.texture.width/2 < 0)ship.move->pos.x += ship.move->speed;
    if(ship.move->pos.y-ship.texture.height/2 < 0)ship.move->pos.y += ship.move->speed;
    if(ship.move->pos.x+ship.texture.width/2 > GetScreenWidth())ship.move->pos.x -= ship.move->speed;
    if(ship.move->pos.y+ship.texture.height/2 > GetScreenHeight())ship.move->pos.y -= ship.move->speed;


    if(ship.move->rotate == CLOCKWISE) ship.move->angle += ship.move->speed*0.5;
    else if(ship.move->rotate == ANTICLOCKWISE) ship.move->angle -= ship.move->speed*0.5;
}


void drawShip(ShipInfo ship){
    DrawTexturePro(ship.texture, (Rectangle){0, 0, ship.texture.width, ship.texture.height}, 
            (Rectangle){(*ship.move).pos.x, (*ship.move).pos.y, ship.texture.width, ship.texture.height}, 
            (Vector2){ship.texture.width / 2.0f, ship.texture.height / 2.0f }, 
            (*ship.move).angle, RAYWHITE);
}


void updateShotPosition(DArray *shotArr, Vector2 size){
    for(size_t i=0; i<shotArr->size; i++){
        MoveInfo* move = (MoveInfo*)shotArr->data[i];
        move->pos.x = move->pos.x + move->speed*cos(DEG2RAD * move->angle);
        move->pos.y = move->pos.y + move->speed*sin(DEG2RAD * move->angle);

        if(move->pos.x-size.x/2 < 0 || move->pos.y-size.y/2 < 0 || 
            move->pos.x+size.x/2 > GetScreenWidth() || move->pos.y+size.y/2 > GetScreenHeight())
        {
            removeDA(shotArr, i);        
        }
    }
}
