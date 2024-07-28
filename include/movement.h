#ifndef _MOVEMENT_H
#define _MOVEMENT_H
#include "main.h"
#include <raylib.h>
#include "moveableElement.h"
#include "darray.h"
#include <math.h>

void captureMoveInput(MoveInfo *move);
float angleBW2Vector(Vector2 pos, Vector2 targetPos);

#endif
