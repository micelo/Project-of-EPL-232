#ifndef ENCODE_TEXT
#define ENCODE_TEXT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<time.h>
#include "decodeStegano.h"
#include"header.h"


int getBit(char *m, int n);
char* readfile_en(FILE *f);
int * createPermutationFunction_en(int N,unsigned int systemkey);
unsigned int right_bit_change(unsigned int a,unsigned int b);
void write_text_to_image(PIXEL *** image, int * permutation,char * m,int height,int width);

#endif