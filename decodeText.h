#ifndef DECODE_TEXT
#define DECODE_TEXT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "header.h"

char *readfile(FILE *f);
int *createPermutationFunction(int N, unsigned int systemkey);
char *create_string_from_image(PIXEL **image, int N, int *permutation, int height, int width, int until);

#endif