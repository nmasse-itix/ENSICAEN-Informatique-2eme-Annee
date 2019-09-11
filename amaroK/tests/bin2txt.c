#include <stdio.h>
#include <stdint.h>

int main(int argc, char ** argv) {

	int16_t sample[2];
	
	while (!feof(stdin)) {
		fread(sample, sizeof(int16_t), 2, stdin);
		printf("%d\n", sample[0]);
	}
	
	return 0;
}
