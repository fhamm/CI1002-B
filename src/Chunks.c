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

void Struct_ElevatedSpikes (int* block, Chunk* chunk) {

    int i;

    for (i = *block; (i < *block + STRUCTURE_SIZE) && (i < CHUNK_SIZE); i++) {
        
        if (i % 2 == 0) {
            chunk->rectangles[i] = 9;
            chunk->triangles[i] = 0;
        }
        else {
            chunk->rectangles[i] = 0;
            chunk->triangles[i] = 9;
        }

        chunk->circles[i] = 0;
    }

    *block = i;

}

// ------------

// Chunk functions

// ------------

Chunk* GenerateChunk (unsigned int seed) {

    // Set randomness and allocate memory
    srand(seed);
    Chunk* chunk = malloc(sizeof(Chunk));

    // This is the jump table (array of pointers) for the structure functions
    StructFunction *StructList[6] = {
        Struct_PlainArea, // 0
        Struct_StairsUp, // 1
        Struct_StairsDown, // 2
        Struct_ElevatedFloor, // 3
        Struct_Spikes, // 4
        Struct_ElevatedSpikes // 5
    };

    // This is the constraint table.
    // It basically tells which structures (columns) are allowed to be placed
    // after a specific structure (row)
    int ConstraintTable[6][6] = {
        {0, 1, 4, -1, -1}, // 0
        {0, 3, 5,-1, -1}, // 1
        {0, 1, 4, -1, -1}, // 2
        {0, 2, 3, 5,  -1}, // 3
        {0, 1, 4, -1, -1}, // 4
        {0, 2, 3,  5, -1}  // 5
    };

    // Generate chunk,
    int block = 0;
    int structure = 0;
    while (block < CHUNK_SIZE) {

        // There is always a flat region on the beginning / end of the chunks
        if ((block < CHUNK_BORDER_SIZE) || (block >= CHUNK_SIZE - CHUNK_BORDER_SIZE))
            structure = 0;
        
        // Generate terrain based on random structure
        StructList[structure](&block, chunk);

        // Find next valid structure randomly
        int nextStructure = -1;
        while (nextStructure == -1) {
            nextStructure = ConstraintTable[structure][rand() % 6];
        }

        structure = nextStructure;
    }

    return chunk;
}

// ------------