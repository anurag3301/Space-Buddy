#ifndef _SHIP_H
#define _SHIP_H

typedef struct{
    size_t fireDelay;
    struct timespec lastFire;
    MoveInfo *shipMove;
    int bulletSpeed;
    DArray *shotArray;
} ShipInfo;

#endif
