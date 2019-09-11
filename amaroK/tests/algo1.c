#include <string.h>

#include "algo1.h"
#include "buffer.h"

static Energy localAverageEnergy = 0;
static FILE * gnuplotDataFile = NULL;
static char * baseName = NULL;
static char gpDataFile[256];


static void computeInstantEnergy(int nb) {
	Energy e = 0;
	int i;
	
	Block * b = block(nb);
	
	for (i = 0; i < N; i++) {
		e += b->samples[i][LEFT] * b->samples[i][LEFT]
			+ b->samples[i][RIGHT] * b->samples[i][RIGHT];
	}
	
	b->instantEnergy = e;
}

static void computeLocalAverageEnergy() {
	int i;
	Energy avgEnergy = 0;
	Block * b = NULL;

	for (i = 0; i < N_BLOCKS; i++) {
		b = block(i);
		avgEnergy += b->instantEnergy;
	}

	localAverageEnergy = avgEnergy / N_BLOCKS;
}

void initAlgo1(char * bn) {
	char str[256];
	
	baseName = bn;
	
	strncpy(str, baseName, 255)[255] = '\0';
	strncat(str, ".dat", 255 - strlen(str));
	
	/* backup file name */
	strncpy(gpDataFile, str, 255)[255] = '\0';
	
	gnuplotDataFile = fopen(gpDataFile, "w");

	fprintf(gnuplotDataFile, "# Gnuplot data file\n");
	fprintf(gnuplotDataFile, "# block nb, instant energy, local avg energ, ratio, der1(ratio)\n");
}

void stepAlgo1(void) {
	int i = curBlock();
	static double prevR = 0;
	
	computeInstantEnergy(i);
		
	if (isBufferFull()) {
		double ratio = (double) block(i)->instantEnergy / (double) localAverageEnergy;
		
		fprintf(gnuplotDataFile, "%8d %16lu ", blocksRead(), block(i)->instantEnergy);
		
		computeLocalAverageEnergy();
		
		fprintf(gnuplotDataFile, "%16lu ", localAverageEnergy);
		fprintf(gnuplotDataFile, "%.3f ", ratio);
		fprintf(gnuplotDataFile, "%.3f ", ratio - prevR);
		fprintf(gnuplotDataFile, "\n");

		prevR = ratio;
	}
}

void finalizeAlgo1(void) {
	char str[256];
	
	fclose(gnuplotDataFile);

	strncpy(str, baseName, 255)[255] = '\0';
	strncat(str, ".plot", 255 - strlen(str));
	
	FILE * gpFile = fopen(str, "w");
	
	fprintf(gpFile, "# GnuPlot instruction file\n");
	fprintf(gpFile, "set xlabel \"samples\"\n");
	fprintf(gpFile, "set ylabel \"relative sound energy\"\n");
	fprintf(gpFile, "set style data lines\n");
	fprintf(gpFile, "set terminal pdf enhanced\n");
	
	strncpy(str, baseName, 255)[255] = '\0';
	strncat(str, "-ratio.pdf", 255 - strlen(str));
	
	fprintf(gpFile, "set output \"%s\"\n", str);
	fprintf(gpFile, "plot \"%s\" using 1:4 title 'Relative sound energy of %s'\n", gpDataFile, baseName);
	
	strncpy(str, baseName, 255)[255] = '\0';
	strncat(str, "-dratio.pdf", 255 - strlen(str));
	
	fprintf(gpFile, "set output \"%s\"\n", str);
	fprintf(gpFile, "set ylabel \"variation of relative sound energy\"\n");
	fprintf(gpFile, "plot \"%s\" using 1:5 title 'Relative sound energy (1st der) of %s'\n", gpDataFile, baseName);

	fclose(gpFile);
}

