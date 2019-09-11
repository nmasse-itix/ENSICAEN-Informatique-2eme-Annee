#include "apodization_functions.h"

#include <math.h>
#include <stdio.h>

void hanning(float * array, int window_width) {
  // scilab equivalent to:
  // a = 0:array_length; array = (1 - cos(2 * %pi * (a / 15))) / 2;

  int i;
  float num_elem = window_width - 1;

  for (i = 0; i < window_width; ++i) {
    array[i] = (1.0 - cos(2.0 * M_PI * (i / num_elem))) / 2;    
  }
}

void test_hanning() {
  float wide8[8];
  float wide19[19];
  int i;

  // test hanning function

  // with 8 wide window
  hanning(wide8, 8);
  printf("hanning(8):\n[%f", wide8[0]);
  for (i = 1; i < 8; ++i) {
    printf(", %f", wide8[i]);
  }
  printf("]\n\n");

  // with 19 wide window
  hanning(wide19, 19);
  printf("hanning(19):\n[%f", wide19[0]);
  for (i = 1; i < 19; ++i) {
    printf(", %f", wide19[i]);
  }
  printf("]\n\n");
}
