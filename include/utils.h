#ifndef _UTILS_H
#define _UTILS_H

#include "calc.h"
#include <raylib.h>

void drawQuadrangle(Quadrangle quad, Color color);

typedef struct SpriteAnimation{
	Texture2D atlas;
	int framesPerSecond;
	float timeStarted;

	Rectangle* rectangles;
	int rectanglesLength;
} SpriteAnimation;

typedef struct{
    double time;
    Vector2 pos;
}AnimationEntry;


SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, uint16_t size, int length);
void UpdateDrawFrameOnce(DArray* animationList, SpriteAnimation animation);

#endif
