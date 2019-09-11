#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define BASE_FREQ 44100
#define BUFFER_SIZE 1024

int16_t buffer[BUFFER_SIZE * 2]; 

int main(int argc, char ** argv) {
	int frequency = 0;
	int bpm = 0;
	double amp = 0;
	int i;
	int t = 0;
	uint64_t t2 = 0;
	int sample_per_beat = 0;
	int beat = 1;
	int duration = 0;
	
	if (argc != 5) {
		fprintf(stderr, "Usage: %s frequency amp bpm duration\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	frequency = atoi(argv[1]);
	amp = atof(argv[2]);
	bpm = atoi(argv[3]);
	duration = atoi(argv[4]);

	sample_per_beat = BASE_FREQ * 60 / bpm;

	fprintf(stderr, "%s: frequency = %d, amp = %f, bpm = %d, duration = %d\n", argv[0], frequency, amp, bpm, duration);

	while (1) {
		for (i = 0; i < BUFFER_SIZE; i++) {
			double sample = 0;
			
			if (beat) {
				double vTime = (double) t * frequency * exp((double) -t * 5 / sample_per_beat) / BASE_FREQ;
				sample = sin(vTime * 2 * M_PI) * exp((double) -t * 5 / sample_per_beat) * amp;
				t++;

				if ((t2 % sample_per_beat) > sample_per_beat / 2) {
					beat = 0;
				}
			}

			if ((t2 % sample_per_beat) == 0) {
				beat = 1;
				t = 0;
			}
			
			t2++;

			buffer[2 * i] = sample * INT16_MAX;
			buffer[2 * i + 1] = sample * INT16_MAX;
		}

		fwrite(buffer, BUFFER_SIZE * 2, sizeof(int16_t), stdout);

		if (t2 > duration * BASE_FREQ) {
			break;
		}
	}
	
	return EXIT_SUCCESS;
}

