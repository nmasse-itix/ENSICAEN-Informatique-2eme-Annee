#include "buffer.h"

static Block historyBuffer[N_BLOCKS];
static int currentBlock = 0;
static int read = 0;

static void nextBlock(void) {
	currentBlock = (currentBlock + 1) % N_BLOCKS;
}


void printBlock(int nb, FILE * st) {
	int i;
	
	for (i = 0; i < N; i++) {
		fprintf(st, "left = %hd\tright = %hd\n", historyBuffer[nb].samples[i][LEFT], 
				historyBuffer[nb].samples[i][RIGHT]);
	}
}

void readBlock(FILE * st) {
	nextBlock();
	fread(historyBuffer[currentBlock].samples, sizeof(Sample), N * 2, st);
	read++;
}

Block * block(int nb) {
	return & (historyBuffer[nb]);
}

int isBufferFull(void) {
	return read >= N_BLOCKS;
}

int curBlock(void) {
	return currentBlock;
}

int blocksRead(void) {
	return read;
}

