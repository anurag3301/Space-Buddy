#ifndef _SHIP_H
#define _SHIP_H
#include <raylib.h>
#include <moveableElement.h>
#include <time.h>
#include <stddef.h>
#include "darray.h"
#include "stdint.h"

typedef struct{
    size_t fireDelay;
    struct timespec lastFire;
    MoveInfo *move;
    int bulletSpeed;
    DArray *bulletArray;
    Texture2D texture; 
    int16_t maxHealth; 
    int16_t health; 
    int16_t damage; 
} ShipInfo;


void updateShipPosition(ShipInfo ship);
void drawShip(ShipInfo);

#endif
