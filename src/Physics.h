#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef ENTITIES
#define ENTITIES
#include "Entities.h"
#endif

// PHYSICS FUNCTIONS

void CalculatePlayerPosition (Player* player, float t);

// Triangle collision check
float TSign (float x1, float y1, float x2, float y2, float x3, float y3);

int PointInsideTriangle (float x, float y, Triangle* triangle);

// Rectangle collision check
int PointInsideRectangle (float x, float y, Rectangle* rectangle);

// Circle collision check
int PointInsideCircle (float x, float y, Circle* circle);

// Player collision check
int PlayerCollisionCheck (Player* player, EntityHandler* entities);