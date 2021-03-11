#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef __PHYSICS__
#define __PHYSICS__
#include "Physics.h"
#endif

#ifndef __ENTITIES__
#define __ENTITIES__
#include "Entities.h"
#endif

// PHYSICS FUNCTIONS

void UpdatePlayerPhysics (Player* player, EntityHandler* entities, float t, int frameCount) {

    // This is where all the physical interactions between the player and the entities
    // are processed. This was, easily, the hardest thing to develop in this game.
    
    int playerBlock = ((ENTITY_X_DISPLACEMENT * frameCount) / BLOCK_SIZE) + PLAYER_START_BLOCK;
    float gravity_y = 0.4;
    float jumpHeight = 40;

    // Update physical properties
    player->ay = gravity_y;
    player->vx += player->ax;
    player->vy += player->ay;
    player->x  += player->vx;
    player->y  += player->vy;

    // Interactions with rectangles
    if (entities->rectangles[playerBlock] != NULL) {

        // For testing purposes
        player->color = entities->rectangles[playerBlock]->color;

        // Calculate distances
        float localFloorHeight = entities->rectangles[playerBlock]->y2;   
        //float verticalDistance = round(localFloorHeight - player->y);
        float displacement = player->y - round(localFloorHeight - player->r);

        if (displacement >= 0) {
            
            // Contact force (normal), where the resultant force is null
            if (displacement <= 50 && entities->rectangles[playerBlock]->jump == 0) {
                player->ay = 0;
                player->vy = 0;
                player->y = round(localFloorHeight - player->r);
            }

            // Jumping
            if ((entities->rectangles[playerBlock]->jump == 1 || player->jumping == 1) && (player->y <= localFloorHeight)) {
                player->vy = -jumpHeight * gravity_y;
            }
        }

        //printf("block = %d jumpable = %d frame = %d vy = %f LocalFloor = %f VD = %f PlayerY = %f jumping = %d displacement = %f\n", playerBlock, entities->rectangles[playerBlock]->jump,frameCount, player->vy, localFloorHeight, verticalDistance, player->y, player->jumping, displacement);
    }
}

// COLLISION FUNCTIONS

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
        
        // Detect collision with triangle block
        if (entities->triangles[block] != NULL)
            if (PointInsideTriangle(player->x, player->y, entities->triangles[block]))
                return 1;
        
        // Detect collision with circle block
        if (entities->circles[block] != NULL)
            if (PointInsideCircle(player->x, player->y, entities->circles[block]))
                return 1;
    }

    return 0;
}

// Check if player is out of bounds
int PlayerOutOfBounds (Player* player) {
    return (player->y >= WINDOW_HEIGHT + player->r);
}
