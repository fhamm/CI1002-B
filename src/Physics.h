#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef __ENTITIES__
#define __ENTITIES__
#include "Entities.h"
#endif

// PHYSICS FUNCTIONS

void UpdatePlayerPhysics (Player* player, EntityHandler* entities, float t, int frameCount);

// Triangle collision check
float TSign (float x1, float y1, float x2, float y2, float x3, float y3);

int PointInsideTriangle (float x, float y, Triangle* triangle);

// COLLISION FUNCTIONS

// Rectangle collision check
int PointInsideRectangle (float x, float y, Rectangle* rectangle);

// Circle collision check
int PointInsideCircle (float x, float y, Circle* circle);

// Player collision check
int PlayerCollisionCheck (Player* player, EntityHandler* entities);

// Check if player is out of bounds
int PlayerOutOfBounds (Player* player);