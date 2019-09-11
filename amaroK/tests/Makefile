CFLAGS =  -Wall -ggdb

all: play gen sef

genStats: genStats.o buffer.o algo1.o

genStats.o: genStats.c buffer.h

buffer.o: buffer.c buffer.h block.h

algo1.o: algo1.c buffer.h algo1.h


apodization_functions.o: apodization_functions.c apodization_functions.h

beatDetectSEF.o: beatDetectSEF.c beatDetectSEF.h

sef: beatDetectSEF.o apodization_functions.o
	$(CC) $(LDFLAGS) -lfftw3f -lm -o $@ $^

play: play.o
	$(CC) $(LDFLAGS) -lasound -o $@ $^

gen: gen.o
	$(CC) $(LDFLAGS) -lm -o $@ $^

.PHONY: all clean

clean:
	rm -f *.o genStats sef play gen toOctave filter apodization_functions
