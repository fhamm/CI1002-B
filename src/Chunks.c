#include <stdio.h>
#include <stdlib.h>

#ifndef CHUNKS
#define CHUNKS
#include "Chunks.h"
#endif

// ------------

// Fundamental game structures

// This is the coolest thing i've ever coded. Basically, you have 
// the GenerateChunk which chooses a set of structures (as described in
// the functions below) and arranges them in a random order.
// Therefore, you have an infinite game that is always being randomly generated 
// based on these basic types of structures.

void Struct_PlainArea (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {
        
        chunk->triangles[i] = 0;
        chunk->rectangles[i] = 1;
        chunk->circles[i] = 0;

    }

    *block = i;
}

void Struct_StairsUp (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {

        if (i - *block == 0)
            chunk->rectangles[i] = 1;
        else
            chunk->rectangles[i] = (i - *block) * (i % 2);

        chunk->triangles[i] = 0;
        chunk->circles[i] = 0;
    
    }

    *block = i;
}

// FIX THIS
void Struct_StairsDown (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {
        
        if (i - *block == 0)
            chunk->rectangles[i] = 1;
        else
            chunk->rectangles[i] = (i - *block) * (i % 2);

        chunk->triangles[i] = 0;
        chunk->circles[i] = 0;

    }

    *block = i;
}

void Struct_ElevatedFloor (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {
        
        chunk->rectangles[i] = 9;
        chunk->triangles[i] = 0;
        chunk->circles[i] = 0;
    }

    *block = i;
}

void Struct_Spikes (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {
        
        if (i % 2 == 0) {
            chunk->rectangles[i] = 1;
            chunk->triangles[i] = 0;
        }
        else {
            chunk->rectangles[i] = 0;
            chunk->triangles[i] = 1;
        }

        chunk->circles[i] = 0;
    }

    *block = i;
}

// ------------

// Chunk functions

// ------------

Chunk* GenerateChunk (unsigned int seed) {

    srand(seed);

    Chunk* chunk = malloc(sizeof(Chunk));

    int block = 0;

    StructFunction *StructList[5] = {
        Struct_PlainArea,
        Struct_StairsUp,
        Struct_StairsDown,
        Struct_ElevatedFloor,
        Struct_Spikes
    };

    while (block < CHUNK_SIZE) {

        int structure = rand() % 5;

        // There is always a flat region on the beginning / end of the chunks
        if ((block < CHUNK_BORDER_SIZE) || (block >= CHUNK_SIZE - CHUNK_BORDER_SIZE))
            structure = 0;
        
        // Generate terrain based on random structure
        StructList[structure](&block, chunk);

        if (structure == 1)
            StructList[3](&block, chunk);

    }

    return chunk;
}

// ------------