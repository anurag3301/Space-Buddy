#include "calc.h"
#include "math.h"
#include "darray.h"
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

Quadrangle rotateQuad(Quadrangle quad, float angle) {
    Vector2 centroid;  
    centroid.x = (quad.p1.x + quad.p2.x + quad.p3.x + quad.p4.x) / 4;
    centroid.y = (quad.p1.y + quad.p2.y + quad.p3.y + quad.p4.y) / 4;

    Vector2 points[4] = {quad.p1, quad.p2, quad.p3, quad.p4};
    for (int i = 0; i < 4; i++) {
        float translatedX = points[i].x - centroid.x;
        float translatedY = points[i].y - centroid.y;

        float rotatedX = translatedX * cos(angle) - translatedY * sin(angle);
        float rotatedY = translatedX * sin(angle) + translatedY * cos(angle);

        points[i].x = rotatedX + centroid.x;
        points[i].y = rotatedY + centroid.y;
    }

    quad.p1 = points[0];
    quad.p2 = points[1];
    quad.p3 = points[2];
    quad.p4 = points[3];

    return quad;
}

Quadrangle texturePosToQuad(Vector2 pos, Texture2D texture){
    Quadrangle quad;
    quad.p1 = (Vector2){pos.x - texture.width/2, pos.y - texture.height/2};
    quad.p2 = (Vector2){pos.x + texture.width/2, pos.y - texture.height/2};
    quad.p3 = (Vector2){pos.x + texture.width/2, pos.y + texture.height/2};
    quad.p4 = (Vector2){pos.x - texture.width/2, pos.y + texture.height/2};

    return quad;
}

DArray* generateRandomCircle(int count){
    DArray* circles = createDArray();

    int gridSize = (int)sqrt(count);
    if (gridSize * gridSize < count) {
        gridSize++;
    }

    int pointsPerCell = (count + gridSize * gridSize - 1) / (gridSize * gridSize);

    float cellWidth =  GetScreenWidth() / gridSize;
    float cellHeight = GetScreenHeight() / gridSize;

    // Initialize random number generator
    srand(time(NULL));

    int index = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            for (int k = 0; k < pointsPerCell && index < count; k++) {
                float cellX = i * cellWidth;
                float cellY = j * cellHeight;

                float randomX = ((float)rand() / RAND_MAX) * cellWidth;
                float randomY = ((float)rand() / RAND_MAX) * cellHeight;

                Circle* circle = malloc(sizeof(Circle));

                circle->pos.x = cellX + randomX;
                circle->pos.y = cellY + randomY;
                circle->radius = GetRandomValue(3, 7);
                circle->color.r = GetRandomValue(10, 250);
                circle->color.g = GetRandomValue(10, 250);
                circle->color.b = GetRandomValue(10, 250);
                circle->color.a = GetRandomValue(50, 150);
                appendDA(circles, circle);
            }
        }
    }

    return circles;
}
