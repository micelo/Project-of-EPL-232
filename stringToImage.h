#ifndef STRING_TO_IMAGE
#define STRING_TO_IMAGE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include"header.h"
#include"decodeStegano.h"

char* file_read(FILE *f);
int _getBit(char *m, int n);
void create_image_with_encoded_text(PIXEL ***image, char * text,int height,int width);

#endif