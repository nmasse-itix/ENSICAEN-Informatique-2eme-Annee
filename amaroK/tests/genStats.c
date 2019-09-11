
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// basename
#define _GNU_SOURCE
#include <libgen.h>

// fork
#include <sys/types.h> 
#include <unistd.h>

#include "buffer.h"
#include "algo1.h"

FILE * decodeMusicFile(char * file) {
	int fd[2] = {0, 0};
	pid_t pid = 0;
	FILE * st = NULL;
	
	char * const execString[] = {"mpg321", "--quiet", "--stdout", file, NULL};

	pipe(fd);

	pid = fork();
	if (pid > 0) {		/* Father */

		/* Close output fd of the pipe */
		close(fd[1]);
		
		/* Open pipe */
		st = fdopen(fd[0], "r");
	} else if (pid == 0) {	/* Son */
		
		/* Close input fd of the pipe */
		close(fd[0]);

		/* Redirect the standard output to the pipe */
		dup2(fd[1], 1);
		
		execvp("mpg321", execString);

		/* exec failed ! */
		perror("execvp");
		exit(1);
	} else {
		perror("fork");
		exit(1);
	}

	return st;
}


int main(int argc, char ** argv) {
	int i = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <music_file>\n", argv[0]);
		exit(1);
	}
	
	char * fileName = argv[1];
	char * baseName = NULL;

	if (strcmp(fileName, "-") == 0) {
		baseName = "stdin";
	} else {
		baseName = basename(fileName);
	}

	initAlgo1(baseName);

	FILE * st = NULL;
	
	if (strcmp(fileName, "-") == 0) {
		st = stdin;
	} else {
		st = decodeMusicFile(fileName);
	}
	
	while (!feof(st)) {
		readBlock(st);
		stepAlgo1();
	}

	finalizeAlgo1();

	return EXIT_SUCCESS;
}
