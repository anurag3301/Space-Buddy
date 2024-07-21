#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include "main.h"
#include <raylib.h>
#include "moveableElement.h"

void UpdateMovement(MoveInfo *move);
void UpdatePosition(MoveInfo *move, Vector2 size);
float faceMouseAngle(Vector2 pos);

#endif
