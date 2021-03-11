#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#ifndef __CONSTANTS__
#define __CONSTANTS__
#include "Constants.h"
#endif

#ifndef __CHUNKS__
#define __CHUNKS__
#include "Chunks.h"
#endif

// ------------

typedef struct Player {
    float x, y, r;
    float vx, vy;
    float ax, ay;
    int jumping;
    ALLEGRO_BITMAP* image;
    ALLEGRO_COLOR color;
} Player;

Player* InitializePlayer ();

void RenderPlayer (Player* player);

// ------------

// Background types & functions

// ------------

typedef struct Background {
    float x;
    ALLEGRO_BITMAP* image;
    ALLEGRO_COLOR color;
} Background;      

Background* InitializeBackground ();

void UpdateBackground (Background* background);

void FreeBackground (Background* background);

// ------------

// Chunk types & functions

// ------------

typedef struct Triangle {
    float x1, y1, x2, y2, x3, y3;
    ALLEGRO_BITMAP* image;
    ALLEGRO_COLOR color;
} Triangle;

typedef struct Rectangle {
    float x1, y1, x2, y2;
    int jump;
    ALLEGRO_BITMAP* image;
    ALLEGRO_COLOR color;
} Rectangle;

typedef struct Circle {
    float cx, cy, r;
    ALLEGRO_BITMAP* image;
    ALLEGRO_COLOR color;
} Circle;

// ------------

// Entity types & functions

// ------------

typedef struct EntityHandler {
    Triangle* triangles[CHUNK_SIZE];
    Rectangle* rectangles[CHUNK_SIZE];
    Circle* circles[CHUNK_SIZE];
} EntityHandler;

EntityHandler* InitializeEntities (Chunk* chunk);

void UpdateEntities (EntityHandler* entities);

void RenderEntities (EntityHandler* entities);

void FreeEntities (EntityHandler* entities);

int ClearSector (EntityHandler* entities, Chunk* chunk); 

// ------------
