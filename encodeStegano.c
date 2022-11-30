/*
 * encodeStegano.c the file for the 3th module of the exercise.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

/**
 * @file encodeStegano.c
 * @author Anna Vasiliou 1070238
 * @brief This file combines a hidden image to a 'cover' image by ;combining the pixels of the two images.
 * More specificaly, by replacing 1,2,3 or 4 least significant bits of the cover image with the corresponding most 
 * significant bits of the hidden image.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * @bug no known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"
#include "encodeStegano.h"
/**
 * @brief integer to binary representation
 * 
 * @param n integer
 * @return char* binary representation
 */
char *_toBin_en(int n)
{
    int c, d, t;
    char *p;

    t = 0;
    p = (char *)malloc(32 + 1);

    if (p == NULL)
        exit(EXIT_FAILURE);

    for (c = 7; c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return p;
}
/**
 * @brief Encode the bit pattern
 * 
 * @param _Cov char pointer to the cover image bit representation
 * @param bitNum number of bits that were replaced
 * @param _toHide char pointer to the hidden image bit representation
 * @return char* 
 */
char *_encode(char *_Cov, int bitNum, char *_toHide)
{
    char *p = (char *)malloc(8 + 1);

    for (int i = 0; i < (8 - bitNum); i++)
    {
        p[i] = _Cov[i];
    }
    for (int i = (8 - bitNum); i < 8; i++)
    {
        p[i] = _toHide[i - 8 + bitNum];
    }
    p[8] = '\0';
    return p;
}
/**
 * @brief binary to int
 * 
 * @param binary char pointer binary representation
 * @return int integer number
 */
int _toInt_en(char *binary)
{
    int pow = 1;
    int res = 0;
    for (int i = 7; i >= 0; i--)
    {
        res += pow * (int)(binary[i] - '0');
        pow *= 2;
    }

    return res;
}
/**
 * @brief write image to encoded file
 * 
 * @param w_file written file
 * @param encoded_image pixel pointer to pointer
 * @param height height image
 * @param width width image
 */
void write_image_to_encoded_file(FILE *w_file, PIXEL **encoded_image, int height, int width)
{
    int padding = ((width * 3) % 4 == 0) ? 0 : 1;
    int tmp = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fwrite(&(encoded_image[i][j].r), 1, 1, w_file);
            fwrite(&(encoded_image[i][j].g), 1, 1, w_file);
            fwrite(&(encoded_image[i][j].b), 1, 1, w_file);
        }
        if (padding)
            fwrite(&tmp, 3, 1, w_file);
    }
    fwrite(&tmp, 1, 1, w_file);
    fwrite(&tmp, 1, 1, w_file);
}
/**
 * @brief write file header
 * 
 * @param w_file written file
 * @param fileheader fileheader pointer
 */
void write_file_header_en(FILE *w_file, FILEHEADER *fileheader)
{
    fwrite(&fileheader->bfType1, 1, 1, w_file);
    fwrite(&fileheader->bfType2, 1, 1, w_file);
    fwrite(&fileheader->bfSize, 4, 1, w_file);
    fwrite(&fileheader->bfReserved1, 2, 1, w_file);
    fwrite(&fileheader->bfReserved2, 2, 1, w_file);
    fwrite(&fileheader->bfOffBits, 4, 1, w_file);
}
/**
 * @brief write info header
 * 
 * @param w_file written file
 * @param infoheader infoheader pointer
 */
void write_info_header_en(FILE *w_file, INFOHEADER *infoheader)
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
/**
 * @brief Create a encoded image object
 * 
 * @param encoded_image pixel pointer to pointer to pointer
 * @param cover_image pixel pointer to pointer 
 * @param toHide_image pixel pointer to pointer
 * @param height height of the image
 * @param width width of the image
 * @param bitNum number of bits that are replaced
 */
void create_encoded_image(PIXEL ***encoded_image, PIXEL **cover_image, PIXEL **toHide_image, int height, int width, int bitNum)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*encoded_image)[i][j].r = (dword)_toInt_en(_encode(_toBin_en((int)cover_image[i][j].r), bitNum, _toBin_en((int)toHide_image[i][j].r)));
            (*encoded_image)[i][j].g = (dword)_toInt_en(_encode(_toBin_en((int)cover_image[i][j].g), bitNum, _toBin_en((int)toHide_image[i][j].g)));
            (*encoded_image)[i][j].b = (dword)_toInt_en(_encode(_toBin_en((int)cover_image[i][j].b), bitNum, _toBin_en((int)toHide_image[i][j].b)));
        }
    }
}

