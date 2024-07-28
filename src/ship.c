#include "ship.h"


void updateShipPosition(ShipInfo ship){
    if(ship.shipMove->moveDir.vertical == UP){
        ship.shipMove->pos.y -= ship.shipMove->speed;
    }
    else if(ship.shipMove->moveDir.vertical == DOWN){
        ship.shipMove->pos.y += ship.shipMove->speed;
    }

    if(ship.shipMove->moveDir.horizontal == RIGHT){
        ship.shipMove->pos.x += ship.shipMove->speed;
    }
    else if(ship.shipMove->moveDir.horizontal == LEFT){
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
