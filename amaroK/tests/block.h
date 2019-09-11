#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>

#define N 1024

typedef enum {LEFT = 0, RIGHT = 1} Channel;

typedef uint64_t Energy;
typedef int16_t Sample;

typedef struct {
	Sample samples[N][2];
	Energy instantEnergy;
} Block;

#endif /* BLOCK_H */

