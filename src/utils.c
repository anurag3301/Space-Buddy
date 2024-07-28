#include "utils.h"
#include <raylib.h>

void drawQuadrangle(Quadrangle quad, Color color){
    DrawLineV(quad.p1, quad.p2, color);
    DrawLineV(quad.p2, quad.p3, color);
    DrawLineV(quad.p3, quad.p4, color);
    DrawLineV(quad.p4, quad.p1, color);
}


Texture2D textureFromImage(const char* filename){
    Image image = LoadImage(filename);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture; 
}
