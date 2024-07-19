#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include "main.h"
#include <raylib.h>

void UpdateMovement(Direction2D *moveDirection, RotationDirection *rotate);
void UpdatePosition(Vector2* pos, float* angle, Direction2D moveDirection, RotationDirection rotate, int speed, Vector2 size);
float faceMouseAngle(Vector2 pos);

#endif
