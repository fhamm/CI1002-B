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

// ------------

// Type definitions

// ------------

typedef struct Chunk {
    char triangles[CHUNK_SIZE];
    char rectangles[CHUNK_SIZE];
    char circles[CHUNK_SIZE];
} Chunk;

// ------------

typedef void StructFunction (int* block, Chunk* chunk);

// ------------

// Fundamental game structures

// This is the coolest thing i've ever coded. Basically, you have 
// the GenerateChunk which chooses a set of structures (as described in
// the functions below) and arranges them in a random order.
// Therefore, you have an infinite game that is always being randomly generated 
// based on these basic types of structures.

void Struct_PlainArea (int* block, Chunk* chunk);
void Struct_StairsUp (int* block, Chunk* chunk);
void Struct_StairsDown (int* block, Chunk* chunk);
void Struct_ElevatedFloor (int* block, Chunk* chunk);
void Struct_Spikes (int* block, Chunk* chunk);
void Struct_ElevatedSpikes (int* block, Chunk* chunk);

// ------------

// Chunk function

Chunk* GenerateChunk (unsigned int seed);

// ------------