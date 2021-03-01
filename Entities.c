#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "Entities.h"

// ------------

Player* InitializePlayer () {

    Player* player = malloc(sizeof(Player));

    player->x = WINDOW_WIDTH / 3;
    player->y = WINDOW_HEIGHT / 2;
    player->r = 30;
    player->color = al_map_rgb(0, 0, 0);

    return player;
}

void RenderPlayer (Player* player, float x, float y) {

    // Update player position
    player->x = x;
    player->y = y;
    player->color = al_map_rgb(255, 255, 255);

    // Render player
    al_draw_filled_circle(player->x, player->y, player->r, player->color);
}

// ------------

// Background types & functions

// ------------

Background* InitializeBackground () {

    Background* background = malloc(sizeof(Background));

    // Initialize as black background
    background->r = 0, background->g = 0, background->b = 0;

   return background;
}

void UpdateBackground (Background* background) {

    // Update background color

    background->r = 15;
    background->g = 15;
    background->b = 30;

    al_clear_to_color(al_map_rgb(background->r, background->g, background->b));
}

// ------------

// Chunk types & functions

// ------------

Chunk* GenerateChunk (unsigned int seed) {

    Chunk* chunk = malloc(sizeof(Chunk));

    int block = 0;

    while (block < CHUNK_SIZE) {

        // Random structures
        int structure = rand() % 4;

        // There is always a flat region on the beginning / end of the chunks
        if ((block < CHUNK_BORDER_SIZE) || (block >= CHUNK_SIZE - CHUNK_BORDER_SIZE))
            structure = 0;

        switch (structure) {
           
            // Plain area
            case 0:
                for (int i = block; i < block + 5; i++) {
                    chunk->triangles[i] = 0;
                    chunk->rectangles[i] = 0;
                    chunk->circles[i] = 0;
                }
                block += 5;
                break;

            // Spikes
            case 1:
                for (int i = block; i < block + 5; i++) {
                    chunk->triangles[i] = 1;
                    chunk->rectangles[i] = 0;
                    chunk->circles[i] = 0;
                }
                block += 5;
                break;

            // Rectangles
            case 2:
                for (int i = block; i < block + 5; i++) {
                    chunk->triangles[i] = 0;
                    chunk->rectangles[i] = 1;
                    chunk->circles[i] = 0;
                }
                block += 5;
                break;

            // Circles
            case 3:
                for (int i = block; i < block + 5; i++) {
                    chunk->triangles[i] = 0;
                    chunk->rectangles[i] = 0;
                    chunk->circles[i] = 1;
                }
                block += 5;
                break;

            // Plain area (default)
            default:
                for (int i = block; i < block + 5; i++) {
                    chunk->triangles[i] = 0;
                    chunk->rectangles[i] = 0;
                    chunk->circles[i] = 0;
                }
                block += 5;
                break;
        }
    }

    return chunk;
}

// ------------

// Entity types & functions

// ------------

EntityHandler* InitializeEntities (Chunk* chunk) {

    EntityHandler* entities = malloc(sizeof(EntityHandler));

    for (int block = 0; block < CHUNK_SIZE; block++) {

        // Initialize triangles
        if (chunk->triangles[block] == 0)
            entities->triangles[block] = NULL;
        else {
            entities->triangles[block] = malloc(sizeof(Triangle));
            Triangle* triangle = entities->triangles[block];
            
            triangle->x1 = block * BLOCK_SIZE;
            triangle->y1 = WINDOW_HEIGHT - FLOOR_HEIGHT;
            triangle->x2 = (block * BLOCK_SIZE) + BLOCK_SIZE;
            triangle->y2 = WINDOW_HEIGHT - FLOOR_HEIGHT;
            triangle->x3 = block * BLOCK_SIZE + (BLOCK_SIZE / 2);
            triangle->y3 = WINDOW_HEIGHT - 2 * (FLOOR_HEIGHT + ENTITY_HEIGHT);

            triangle->color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
        }

        // Initialize rectangles
        if (chunk->rectangles[block] == 0)
            entities->rectangles[block] = NULL;
        else {
            entities->rectangles[block] = malloc(sizeof(Rectangle));
            Rectangle* rectangle = entities->rectangles[block];
            
            rectangle->x1 = block * BLOCK_SIZE;
            rectangle->y1 = WINDOW_HEIGHT - FLOOR_HEIGHT;
            rectangle->x2 = (block * BLOCK_SIZE) + BLOCK_SIZE;
            rectangle->y2 = WINDOW_HEIGHT - (FLOOR_HEIGHT + ENTITY_HEIGHT);

            rectangle->color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
        }

        // Initialize circles
        if (chunk->circles[block] == 0)
            entities->circles[block] = NULL;
        else {
            entities->circles[block] = malloc(sizeof(Circle));
            Circle* circle = entities->circles[block];
            
            circle->cx = block * BLOCK_SIZE + (BLOCK_SIZE / 2);
            circle->cy = rand() % WINDOW_HEIGHT;
            circle->r  = ENTITY_HEIGHT;

            circle->color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
        }
    }

    return entities;
}

void UpdateEntities (EntityHandler* entities) {

    // Update triangles
    for (int block = 0; block < CHUNK_SIZE; block++) {

        Triangle* triangle = entities->triangles[block];

        if (triangle == NULL)
            continue;

        triangle->x1 -= ENTITY_X_DISPLACEMENT;
        triangle->x2 -= ENTITY_X_DISPLACEMENT;
        triangle->x3 -= ENTITY_X_DISPLACEMENT;
    }

    // Update rectangles
    for (int block = 0; block < CHUNK_SIZE; block++) {
        
        Rectangle* rectangle = entities->rectangles[block];

        if (rectangle == NULL)
            continue;

        rectangle->x1 -= ENTITY_X_DISPLACEMENT;
        rectangle->x2 -= ENTITY_X_DISPLACEMENT;
    }

    // Update circles
    for (int block = 0; block < CHUNK_SIZE; block++) {
        
        Circle* circle = entities->circles[block];

        if (circle == NULL)
            continue;

        circle->cx -= ENTITY_X_DISPLACEMENT;
    }
}

void RenderEntities (EntityHandler* entities) {

    // Render triangles
    for (int block = 0; block < CHUNK_SIZE; block++) {  

        Triangle* triangle = entities->triangles[block];

        if (triangle != NULL)
            al_draw_filled_triangle(triangle->x1, triangle->y1, triangle->x2, triangle->y2, triangle->x3, triangle->y3, triangle->color);
    }

    // Render rectangles
    for (int block = 0; block < CHUNK_SIZE; block++) {

        Rectangle* rectangle = entities->rectangles[block];
        
        if (rectangle != NULL)
            al_draw_filled_rectangle(rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2, rectangle->color);  
    }

    // Render circles
    for (int block = 0; block < CHUNK_SIZE; block++) {

        Circle* circle = entities->circles[block];

        if (circle != NULL)
            al_draw_filled_circle(circle->cx, circle->cy, circle->r, circle->color); 
    }
}

void FreeEntities (EntityHandler* entities) {

    for (int block = 0; block < CHUNK_SIZE; block++) {

        // Free triangles
        if (entities->triangles[block] != NULL)
            free(entities->triangles[block]);

        // Free rectangles
        if (entities->rectangles[block] != NULL)
            free(entities->rectangles[block]);

        // Free circles
        if (entities->circles[block] != NULL)
            free(entities->circles[block]);
    }

    free(entities);
}

int ClearSector (EntityHandler* entities, Chunk* chunk) {

    for (int block = 0; block < CHUNK_SIZE; block++) {

        if (entities->triangles[block] != NULL)
            if (entities->triangles[block]->x2 >= 0)
                return 0;

        if (entities->rectangles[block] != NULL)
            if (entities->rectangles[block]->x2 >= 0)
                return 0;

        if (entities->circles[block] != NULL)
            if (entities->circles[block]->cx >= 0)
                return 0;

    }

    printf("New sector initialized!\n");
    free(chunk);
    FreeEntities(entities);

    return 1;
} 

// ------------