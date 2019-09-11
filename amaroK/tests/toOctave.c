#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int16_t * buffer = NULL;

int main(int argc, char ** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s nSamples name\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int nSamples = atoi(argv[1]);
	char * name = argv[2];
	int n = 0;
	int i = 0;
	
	buffer = malloc(sizeof(int16_t) * nSamples * 2);
	
	while (n < nSamples && (! feof(stdin))) {
		int ret = fread(buffer + (n * 2), 2, sizeof(int16_t), stdin);
		if (ret != 2) {
			break;
		}
		
		n++;
	}

	printf("# name: %s_l\n", name);
	printf("# type: matrix\n");
	printf("# rows: 1\n");
	printf("# columns: %d\n", n);
	for (i = 0; i < n; i++) {
		printf("%d ", (int) buffer[2 * i]);
	}
	printf("\n");
	printf("# name: %s_r\n", name);
	printf("# type: matrix\n");
	printf("# rows: 1\n");
	printf("# columns: %d\n", n);
	for (i = 0; i < n; i++) {
		printf("%d ", (int) buffer[2 * i + 1]);
	}
	printf("\n");
	
	free(buffer);

	return EXIT_SUCCESS;
}

