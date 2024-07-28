#include "ship.h"
#include <math.h>


void updateShipPosition(ShipInfo ship){
    if(ship.shipMove->direction.vertical == UP){
        ship.shipMove->pos.y -= ship.shipMove->speed;
    }
    else if(ship.shipMove->direction.vertical == DOWN){
        ship.shipMove->pos.y += ship.shipMove->speed;
    }

    if(ship.shipMove->direction.horizontal == RIGHT){
        ship.shipMove->pos.x += ship.shipMove->speed;
    }
    else if(ship.shipMove->direction.horizontal == LEFT){
        ship.shipMove->pos.x -= ship.shipMove->speed;
    }

    if(ship.shipMove->pos.x-ship.texture.width/2 < 0)ship.shipMove->pos.x += ship.shipMove->speed;
    if(ship.shipMove->pos.y-ship.texture.height/2 < 0)ship.shipMove->pos.y += ship.shipMove->speed;
    if(ship.shipMove->pos.x+ship.texture.width/2 > GetScreenWidth())ship.shipMove->pos.x -= ship.shipMove->speed;
    if(ship.shipMove->pos.y+ship.texture.height/2 > GetScreenHeight())ship.shipMove->pos.y -= ship.shipMove->speed;


    if(ship.shipMove->rotate == CLOCKWISE) ship.shipMove->angle += ship.shipMove->speed*0.5;
    else if(ship.shipMove->rotate == ANTICLOCKWISE) ship.shipMove->angle -= ship.shipMove->speed*0.5;
}


void drawShip(ShipInfo ship){
    DrawTexturePro(ship.texture, (Rectangle){0, 0, ship.texture.width, ship.texture.height}, 
            (Rectangle){(*ship.shipMove).pos.x, (*ship.shipMove).pos.y, ship.texture.width, ship.texture.height}, 
            (Vector2){ship.texture.width / 2.0f, ship.texture.height / 2.0f }, 
            (*ship.shipMove).angle, RAYWHITE);
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
