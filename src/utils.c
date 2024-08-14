#include "utils.h"
#include <raylib.h>
#include <stdlib.h>

void drawQuadrangle(Quadrangle quad, Color color){
    DrawLineV(quad.p1, quad.p2, color);
    DrawLineV(quad.p2, quad.p3, color);
    DrawLineV(quad.p3, quad.p4, color);
    DrawLineV(quad.p4, quad.p1, color);
}

SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, uint16_t size, int length){
	SpriteAnimation spriteAnimation ={
		.atlas = atlas,
		.framesPerSecond = framesPerSecond,
		.rectangles = NULL,
		.rectanglesLength = length
	};
	
	Rectangle* mem = (Rectangle*)malloc(sizeof(Rectangle) * length);

	spriteAnimation.rectangles = mem;

	for (int i = 0; i < length; i++){
		spriteAnimation.rectangles[i] = (Rectangle){i*220, 0, 220, 220};		
	}

	return spriteAnimation;
}

void UpdateDrawFrameOnce(DArray* animationList, SpriteAnimation animation){
    for(size_t i=0; i<animationList->size; i++){
        AnimationEntry *entry = animationList->data[i];
        Rectangle dest = {entry->pos.x, entry->pos.y,  60, 60 };
        Vector2 origin = { 0 };
        int index = (int)((GetTime() - entry->time) * animation.framesPerSecond);
        if(index >= animation.rectanglesLength){
            removeDA(animationList, i);
            continue;
        }

        Rectangle source = animation.rectangles[index];
        DrawTexturePro(animation.atlas, source, dest, origin, 0, WHITE);
    }
}
