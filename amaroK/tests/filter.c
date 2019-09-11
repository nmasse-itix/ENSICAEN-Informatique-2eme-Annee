#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// M must be an even integer
#define M 256

// Gain
double k = 1.0;

const int sfreq = 44100;
const int max_freq = sfreq / 2;

double kernel[M + 1];

// fc is the cut off frequency (between 0 and 0.5)
double fc = 0.01;

int main(int argc, char ** argv) {
  int i;

  // generate kernel
  for (i = 0; i <= M; i++) {
	  if (i == M / 2) {
		kernel[i] = 2 * M_PI * fc;
	  } else {
	  	kernel[i] = (sin(2 * M_PI * fc * (i - (M / 2))) / (i - (M / 2))) 
		  	* (0.42 - 0.5 * cos(2 * M_PI * (double) i / M) 
				+ 0.08 cos(4 * M_PI * (double) i / M));
	  }


  }

  while (1) {
		
    fread(x_n, 2, sizeof(int16_t), stdin);
		
    y_n[0] = (a * ((double) x_n[0] + (double) x_nm1[0]) + b * y_nm1[0]);
    y_n[1] = (a * ((double) x_n[1] + (double) x_nm1[1]) + b * y_nm1[1]);

		
    fwrite(y_n, 2, sizeof(int16_t), stdout);
    x_nm1[0] = x_n[0];
    x_nm1[1] = x_n[1];
    y_nm1[0] = y_n[0];
    y_nm1[1] = y_n[1];
		
  }
	
  return EXIT_SUCCESS;
}

