
#include "header.h"
#include "grayscale_bmp.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>



void alloc_image_mem(PIXEL ***image_grayscale,int height,int width){
    *image_grayscale = (PIXEL **)malloc(height * sizeof(PIXEL *));
    if(*image_grayscale == NULL){
        fprintf(stderr, "Memory allocation failed\n");
    }
    for(int i = 0; i < height; i++){
        (*image_grayscale)[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
    }
}

void cpy_to_image_grayscale(PIXEL ***image_grayscale,PIXEL ** image,int height,int width){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            (*image_grayscale)[i][j] = image[i][j];
        }
    }
}

void to_grayscale(PIXEL *** image_grayscale,int height,int width){
    
}

