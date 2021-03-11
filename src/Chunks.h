#include <stdio.h>
#include <stdlib.h>

#ifndef __CONSTANTS__
#include "Constants.h"
#endif

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
void Struct_Holes (int* block, Chunk* chunk);
void Struct_ElevatedHoles (int* block, Chunk* chunk);
void Struct_Saws (int* block, Chunk* chunk);

// ------------

// Chunk function

Chunk* GenerateChunk (unsigned int seed);

// ------------
