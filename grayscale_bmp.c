/*
 * grayscale.c the file for the 2th module of the exercise.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

/**
 * @file grayscale_bmp.c
 * @author Anna Vasiliou 1070238
 * @brief This file converts a bmp image to a black and white image by changing the pixels of the original image.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "header.h"
#include "grayscale_bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
/**
 * @brief Allocate memory for the image data
 * 
 * @param image_grayscale pixel pointer to pointer to pointer
 * @param height height of the image
 * @param width width of the image
 */
void alloc_image_mem(PIXEL ***image_grayscale, int height, int width)
{
    *image_grayscale = (PIXEL **)malloc(height * sizeof(PIXEL *));
    if (*image_grayscale == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
    }
    for (int i = 0; i < height; i++)
    {
        (*image_grayscale)[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
    }
}
/**
 * @brief copies image data to grayscale 
 * 
 * @param image_grayscale pixel pointer to pointer to pointer 
 * @param image pixel pointer to pointer
 * @param height height of image
 * @param width width of image
 */
void cpy_to_image_grayscale(PIXEL ***image_grayscale, PIXEL **image, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*image_grayscale)[i][j] = image[i][j];
        }
    }
}
/**
 * @brief This functions calculates the new rgb of the grayscale image
 * 
 * @param image_grayscale pixel pointer to pointer to pointer
 * @param height height of the grayscale image
 * @param width width of the grayscale image
 */
void to_grayscale(PIXEL ***image_grayscale, int height, int width)
{
    int cnt = 0;
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            cnt = 0;
            cnt += roundf((*image_grayscale)[i][j].r * 0.299);
            cnt += roundf((*image_grayscale)[i][j].g * 0.587);
            cnt += roundf((*image_grayscale)[i][j].b * 0.114);
            (*image_grayscale)[i][j].r = (*image_grayscale)[i][j].g = (*image_grayscale)[i][j].b = cnt;
        }
    }
}
/**
 * @brief writes the new gray pixels to the image
 * 
 * @param w_file file pointer
 * @param image_grayscale pixel pointer to pointer
 * @param height height of the image
 * @param width width of the image
 */
void write_gray_pixels(FILE *w_file, PIXEL **image_grayscale, int height, int width)
{
    int padding = ((width * 3) % 4 == 0) ? 0 : 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fwrite(&image_grayscale[i][j].r, 1, 1, w_file);
            fwrite(&image_grayscale[i][j].g, 1, 1, w_file);
            fwrite(&image_grayscale[i][j].b, 1, 1, w_file);
        }
        int tmp = 0;
        if (padding)
            fwrite(&tmp, 3, 1, w_file);
    }
    int tmp = 0;
    // if(padding){
    // fwrite(&tmp, 1, 1, w_file);
    // fwrite(&tmp, 1, 1, w_file);
    // }
}
/**
 * @brief writes the new file header
 * 
 * @param w_file file pointer
 * @param fileheader fileheader pointer
 */
void write_gray_file_header(FILE *w_file, FILEHEADER *fileheader)
{
    fwrite(&fileheader->bfType1, 1, 1, w_file);
    fwrite(&fileheader->bfType2, 1, 1, w_file);
    fwrite(&fileheader->bfSize, 4, 1, w_file);
    fwrite(&fileheader->bfReserved1, 2, 1, w_file);
    fwrite(&fileheader->bfReserved2, 2, 1, w_file);
    fwrite(&fileheader->bfOffBits, 4, 1, w_file);
}
/**
 * @brief writes the new info header
 * 
 * @param w_file file pointer
 * @param infoheader infoheader pointer
 */
void write_gray_info_header(FILE *w_file, INFOHEADER *infoheader)
{
    fwrite(&infoheader->biSize, 4, 1, w_file);
    fwrite(&infoheader->biWidth, 4, 1, w_file);
    fwrite(&infoheader->biHeight, 4, 1, w_file);
    fwrite(&infoheader->biPlanes, 2, 1, w_file);
    fwrite(&infoheader->biBitCount, 2, 1, w_file);
    fwrite(&infoheader->biCompression, 4, 1, w_file);
    fwrite(&infoheader->biSizeImage, 4, 1, w_file);
    fwrite(&infoheader->biXPelsPerMeter, 4, 1, w_file);
    fwrite(&infoheader->biYPelsPerMeter, 4, 1, w_file);
    fwrite(&infoheader->biClrUsed, 4, 1, w_file);
    fwrite(&infoheader->biClrImportant, 4, 1, w_file);
}

/*
int main(){



    return 0;
}*/