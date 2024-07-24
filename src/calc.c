#include "calc.h"
#include "math.h"

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
