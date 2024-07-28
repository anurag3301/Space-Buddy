#ifndef _SHIP_H
#define _SHIP_H
#include <raylib.h>
#include <moveableElement.h>
#include <time.h>
#include <stddef.h>
#include "darray.h"

typedef struct{
    size_t fireDelay;
    struct timespec lastFire;
    MoveInfo *shipMove;
    int bulletSpeed;
    DArray *shotArray;
    Texture2D texture; 
} ShipInfo;


void updateShipPosition(ShipInfo ship);
void drawShip(ShipInfo);

#endif
