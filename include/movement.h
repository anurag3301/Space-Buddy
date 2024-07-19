#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include "main.h"
#include <raylib.h>

void UpdateMovement(Direction2D *moveDirection);
void UpdatePosition(Vector2* pos, Direction2D moveDirection, int speed);

#endif
