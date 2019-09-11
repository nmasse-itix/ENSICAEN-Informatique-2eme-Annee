#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h>

#include "block.h"

#define N_BLOCKS 43
#define N_SAMPLES (N_BLOCKS * N)

void readBlock(FILE * st);
void printBlock(int nb, FILE * st);
Block * block(int nb);
int isBufferFull(void);
int curBlock(void);
int blocksRead(void);

#endif /* BUFFER_H */

