#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#ifndef CHUNKS
#define CHUNKS
#include "Chunks.h"
#endif

#ifndef ENTITIES
#define ENTITIES
#include "Entities.h"
#endif

// ------------

Player* InitializePlayer () {

    Player* player = malloc(sizeof(Player));

    player->x = WINDOW_WIDTH / 3;
    player->y = WINDOW_HEIGHT / 2;
    player->r = 30;
    player->vx = 0;
    player->vy = 0;
    player->ax = 0;
    player->ay = 0;
    player->m = 1.5;
    player->color = al_map_rgb(0, 0, 0);

    return player;
}

void RenderPlayer (Player* player, float x, float y) {

    // Update player position
    player->x = x;
    player->y = y;
    player->ax = 0;
    player->ay = 0;
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

            triangle->color = al_map_rgb(/*rand() % */255, /*rand() % */255, /*rand() % */255);
        }

        // Initialize rectangles
        if (chunk->rectangles[block] == 0)
            entities->rectangles[block] = NULL;
        else {
            entities->rectangles[block] = malloc(sizeof(Rectangle));
            Rectangle* rectangle = entities->rectangles[block];
            
            rectangle->x1 = block * BLOCK_SIZE;
            rectangle->x2 = (block * BLOCK_SIZE) + BLOCK_SIZE;

            rectangle->y1 = (WINDOW_HEIGHT - FLOOR_HEIGHT) - ((chunk->rectangles[block] - 1) * WINDOW_HEIGHT / 20);
            rectangle->y2 = (WINDOW_HEIGHT - WINDOW_HEIGHT / 20) - ((chunk->rectangles[block] - 1) * WINDOW_HEIGHT / 20);

            rectangle->color = al_map_rgb(/*rand() % */255, /*rand() % */255, /*rand() % */255);
        }

        // Initialize circles
        if (chunk->circles[block] == 0)
            entities->circles[block] = NULL;
        else {
            entities->circles[block] = malloc(sizeof(Circle));
            Circle* circle = entities->circles[block];
            
            circle->cx = block * BLOCK_SIZE + (BLOCK_SIZE / 2);
            circle->cy = rand() % WINDOW_HEIGHT;
            circle->r  = ENTITY_HEIGHT + (rand() % 2 * ENTITY_HEIGHT);

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