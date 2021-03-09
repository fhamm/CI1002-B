#ifndef ENVIRONMENT_VARS

#define GAME_FPS 60 // Refresh rate of the game, in FPS
#define WINDOW_WIDTH 1920 // Game window width, in pixels
#define WINDOW_HEIGHT 1080 // Game window height, in pixels
#define CHUNK_SIZE 500 // Chunk size, in blocks
#define CHUNK_BORDER_SIZE 15 // Chunk border size, in blocks
#define STRUCTURE_SIZE 10 // Maximum size of fundamental game structures, in blocks
#define BLOCK_SIZE 150 // Block size, in pixels
#define ENTITY_X_DISPLACEMENT 10 // Entity displacement in the X axis, in pixels
#define FLOOR_HEIGHT 0 // Height of the floor, in pixels
#define ENTITY_HEIGHT 50 // Height of entities, in pixels
#define RANDOM_SEED 12039102 // Random number seed
#define PLAYER_START_BLOCK 5

#endif

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