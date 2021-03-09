#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
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

    player->x = PLAYER_START_BLOCK * BLOCK_SIZE;
    player->y = WINDOW_HEIGHT - 150;

    player->image = al_load_bitmap("resources/graphics/player.png");
    if (player->image == NULL) {
        perror("Could not load player sprite\n");
        exit(1);
    }

    player->r = al_get_bitmap_width(player->image) / 2;

    player->vx = 0;
    player->vy = 0;
    player->ax = 0;
    player->ay = 0;
    player->jumping = 0;

    player->color = al_map_rgb(0, 0, 0);

    return player;
}

void RenderPlayer (Player* player) {

    // This only works here. Why?
    player->image = al_load_bitmap("resources/graphics/player.png");
    if (player->image == NULL) {
        perror("Could not load player sprite\n");
        exit(1);
    }

    // Render player
    //if (player->image != NULL)
    al_draw_bitmap(player->image, player->x - player->r, player->y - player->r, 0);
    //al_draw_filled_circle(player->x, player->y, player->r, player->color); 


    al_destroy_bitmap(player->image);
}

// ------------

// Background types & functions

// ------------

Background* InitializeBackground () {

    Background* background = malloc(sizeof(Background));
    
    background->image = al_load_bitmap("resources/graphics/background.png");
    if (background->image == NULL) {
        perror("Could not load background\n");
        exit(1);
    }

    background->x = 0;

   return background;
}

void UpdateBackground (Background* background) {

    // Update background color
    al_clear_to_color(al_map_rgb(0, 0, 0));

    float backgroundImageWidth = al_get_bitmap_width (background->image);

    if (background->x + backgroundImageWidth <= 0)
        background->x = 0;

    // Draw background
    al_draw_bitmap(background->image, background->x , 0, 0);
    al_draw_bitmap(background->image, background->x + backgroundImageWidth, 0, 0);

    background->x -= ENTITY_X_DISPLACEMENT;
}

void FreeBackground (Background* background) {
    al_destroy_bitmap (background->image);
    free(background);
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

            char value = chunk->triangles[block];
            
            triangle->x1 = block * BLOCK_SIZE;
            triangle->y1 = WINDOW_HEIGHT - FLOOR_HEIGHT - ((value - 1) * WINDOW_HEIGHT / 20);
            triangle->x2 = (block * BLOCK_SIZE) + BLOCK_SIZE;
            triangle->y2 = WINDOW_HEIGHT - FLOOR_HEIGHT - ((value - 1) * WINDOW_HEIGHT / 20);
            triangle->x3 = block * BLOCK_SIZE + (BLOCK_SIZE / 2);
            triangle->y3 = WINDOW_HEIGHT - FLOOR_HEIGHT - 2 * (FLOOR_HEIGHT + ENTITY_HEIGHT) - ((value - 1) * WINDOW_HEIGHT / 20);

            triangle->image = al_load_bitmap("resources/graphics/triangle.png");

            if (triangle->image == NULL) {
                perror("Could not load triangle sprite\n");
                exit(1);
            }

            triangle->color = al_map_rgb(255, 0, 0);
        }

        // Initialize rectangles
        if (chunk->rectangles[block] == 0)
            entities->rectangles[block] = NULL;
        else {
            entities->rectangles[block] = malloc(sizeof(Rectangle));
            Rectangle* rectangle = entities->rectangles[block];

            char value = chunk->rectangles[block];

            rectangle->jump = 0;

            if (value < 0) {
                rectangle->jump = 1;
                rectangle->color = al_map_rgb(255, 255, 255);
                value = -value;
            }
            else {
                rectangle->color = al_map_rgb(0, 0, 0);
            }
            
            rectangle->x1 = block * BLOCK_SIZE;
            rectangle->x2 = (block * BLOCK_SIZE) + BLOCK_SIZE;

            rectangle->y1 = (WINDOW_HEIGHT - FLOOR_HEIGHT) - ((value - 1) * WINDOW_HEIGHT / 20);
            rectangle->y2 = (WINDOW_HEIGHT - WINDOW_HEIGHT / 20) - ((value - 1) * WINDOW_HEIGHT / 20);

            rectangle->image = al_load_bitmap("resources/graphics/rectangle.png");

            if (rectangle->image == NULL) {
                perror("Could not load rectangle sprite\n");
                exit(1);
            }
        }

        // Initialize circles
        if (chunk->circles[block] == 0)
            entities->circles[block] = NULL;
        else {
            entities->circles[block] = malloc(sizeof(Circle));
            Circle* circle = entities->circles[block];

            char value = chunk->circles[block];

            
            circle->cx = block * BLOCK_SIZE + (BLOCK_SIZE / 2);
            circle->cy = WINDOW_HEIGHT - (2 * FLOOR_HEIGHT) - (value * ENTITY_HEIGHT);
            circle->r  = ENTITY_HEIGHT;

            circle->color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);

            circle->image = al_load_bitmap("resources/graphics/circle.png");
            if (circle->image == NULL) {
                perror("Could not load circle sprite\n");
                exit(1);
            }
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
        
        if (triangle != NULL) {
            //al_draw_bitmap(triangle->image, triangle->x1, triangle->y3, 0);
            al_draw_filled_triangle(triangle->x1, triangle->y1, triangle->x2, triangle->y2, triangle->x3, triangle->y3, triangle->color);
        }
    }

    // Render rectangles
    for (int block = 0; block < CHUNK_SIZE; block++) {

        Rectangle* rectangle = entities->rectangles[block];
        
        if (rectangle != NULL) {
            //al_draw_bitmap(rectangle->image, rectangle->x1, rectangle->y2, 0);
            al_draw_filled_rectangle(rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2, rectangle->color);  
        }
    }

    // Render circles
    for (int block = 0; block < CHUNK_SIZE; block++) {

        Circle* circle = entities->circles[block];

        if (circle != NULL) {
            //al_draw_bitmap(circle->image, circle->cx - circle->r, circle->cy - circle->r, 0);
            al_draw_filled_circle(circle->cx, circle->cy, circle->r, circle->color); 
        }
    }
}

void FreeEntities (EntityHandler* entities) {

    for (int block = 0; block < CHUNK_SIZE; block++) {

        // Free triangles
        if (entities->triangles[block] != NULL) {
            al_destroy_bitmap(entities->triangles[block]->image);
            free(entities->triangles[block]);
        }

        // Free rectangles
        if (entities->rectangles[block] != NULL) {
            al_destroy_bitmap(entities->rectangles[block]->image);
            free(entities->rectangles[block]);
        }

        // Free circles
        if (entities->circles[block] != NULL) {
            al_destroy_bitmap(entities->circles[block]->image);
            free(entities->circles[block]);
        }
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