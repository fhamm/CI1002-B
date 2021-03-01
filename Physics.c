#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Entities.h"
#include "Physics.h"

// Triangle collision check
float TSign (float x1, float y1, float x2, float y2, float x3, float y3) {
    return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}

int PointInsideTriangle (float x, float y, Triangle* triangle) {

    float d1, d2, d3;
    int hasNegative, hasPositive;

    d1 = TSign(x, y, triangle->x1, triangle->y1, triangle->x2, triangle->y2);
    d2 = TSign(x, y, triangle->x2, triangle->y2, triangle->x3, triangle->y3);
    d3 = TSign(x, y, triangle->x3, triangle->y3, triangle->x1, triangle->y1);

    hasNegative = (d1 < 0) || (d2 < 0) || (d3 < 0);
    hasPositive = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(hasNegative && hasPositive);
}

// Rectangle collision check
int PointInsideRectangle (float x, float y, Rectangle* rectangle) {
    return ((x > rectangle->x1) && (x < rectangle->x2) && (y < rectangle->y1) && (y > rectangle->y2));
}

// Circle collision check
int PointInsideCircle (float x, float y, Circle* circle) {
    return pow((x - circle->cx), 2) + pow((y - circle->cy), 2) < pow((circle->r), 2);
}

// Player collision check
int PlayerCollisionCheck (Player* player, EntityHandler* entities) {

    for (int block = 0; block < CHUNK_SIZE; block++) {

        if (entities->triangles[block] != NULL)
            if (PointInsideTriangle(player->x, player->y, entities->triangles[block]))
                return 1;

        if (entities->rectangles[block] != NULL)
            if (PointInsideRectangle(player->x, player->y, entities->rectangles[block]))
                return 1;

        if (entities->circles[block] != NULL)
            if (PointInsideCircle(player->x, player->y, entities->circles[block]))
                return 1;
    }

    return 0;
}