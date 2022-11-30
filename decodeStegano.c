/*
 * decodeStegano.c the file for the 4th module of the exercise, decoding an image from an image.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

/**
 * @file decodeStegano.c
 * @author Anna Vasiliou 1070238
 * @brief This file decodes the hidden image from the new image that was created in the encodeStegano module.
 * @version 0.1
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 * @bug no known bugs
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "decodeStegano.h"
/**
 * @brief Function that converts integer to string binary representation
 * 
 * @param n integer number
 * @return char* character pointer that represents binary number
 */
char *_toBin(int n)
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
 * @brief binary representation to integer number
 * 
 * @param binary character pointer
 * @return int integer number
 */
int _toInt(char *binary)
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
 * @brief Decodes a binary string by replacing its 'bitNum' bits with other 
 * digits (of the other image)
 * 
 * @param binary character pointer, binary representation
 * @param bitNum number of bits that are going to be replaced
 * @return char* decoded binary representation
 */
char *decode(char *binary, int bitNum)
{
    char *res = (char *)malloc(8 + 1);

    for (int i = 0; i < (8 - bitNum); i++)
    {
        res[i] = binary[i + bitNum];
    }
    for (int i = (8 - bitNum); i < 8; i++)
    {
        res[i] = '0';
    }
    res[8] = '\0';
    return res;
}
/**
 * @brief Changes the rgb of the image to create a decoded image.
 * 
 * @param orig_image pixel pointer to pointer
 * @param decoded_image pixel pointer to pointer to pointer 
 * @param height height of the image
 * @param width width of the image
 * @param bitNum number of bits that are going to be replaced
 */
void create_decoded_image(PIXEL **orig_image, PIXEL ***decoded_image, int height, int width, int bitNum)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*decoded_image)[i][j].r = (dword)_toInt(decode(_toBin((int)orig_image[i][j].r), bitNum));
            (*decoded_image)[i][j].g = (dword)_toInt(decode(_toBin((int)orig_image[i][j].g), bitNum));
            (*decoded_image)[i][j].b = (dword)_toInt(decode(_toBin((int)orig_image[i][j].b), bitNum));
        }
    }
}
/**
 * @brief Writes image to the output file using padding.
 * 
 * @param w_file file that is going to be written
 * @param decoded_image pixel pointer to pointer
 * @param height height of the image
 * @param width width of the image
 */
void write_image_to_decoded_file(FILE *w_file, PIXEL **decoded_image, int height, int width)
{
    int padding = ((width * 3) % 4 == 0) ? 0 : 1;
    int tmp = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fwrite(&(decoded_image[i][j].r), 1, 1, w_file);
            fwrite(&(decoded_image[i][j].g), 1, 1, w_file);
            fwrite(&(decoded_image[i][j].b), 1, 1, w_file);
        }
        if (padding)
            fwrite(&tmp, 3, 1, w_file);
    }
    fwrite(&tmp, 1, 1, w_file);
    fwrite(&tmp, 1, 1, w_file);
}
/**
 * @brief Writes the file header by changing all of the structures fields to the new ones.
 * 
 * @param w_file file that is going to be written
 * @param fileheader fileheader pointer
 */
void write_file_header(FILE *w_file, FILEHEADER *fileheader)
{
    fwrite(&fileheader->bfType1, 1, 1, w_file);
    fwrite(&fileheader->bfType2, 1, 1, w_file);
    fwrite(&fileheader->bfSize, 4, 1, w_file);
    fwrite(&fileheader->bfReserved1, 2, 1, w_file);
    fwrite(&fileheader->bfReserved2, 2, 1, w_file);
    fwrite(&fileheader->bfOffBits, 4, 1, w_file);
}
/**
 * @brief Writes the file header by changing all of the structure fields to the new ones.
 * 
 * @param w_file file that is going to be written
 * @param infoheader infoheader pointer
 */
void write_info_header(FILE *w_file, INFOHEADER *infoheader)
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
    //printf("THIS IS A TEST : %s\n",decode(_toBin(95),4));
    //printf("THIS IS A TEST : %u\n",(dword)_toInt(decode(_toBin(test),4)));
    FILEHEADER * fileheader = (FILEHEADER * )malloc(sizeof(FILEHEADER));
    INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * file = fopen("ENCODED_IMAGE.bmp", "r");
    FILE * decoded_file = fopen("DECODED_IMAGE.bmp", "w+");
    read_file_header(file,&fileheader);
    read_info_header(file,&infoheader);
    PIXEL ** image, **decoded_image;
    image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
    decoded_image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
    for(int i = 0 ; i < infoheader->biHeight;i++){
        image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
        decoded_image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
    }
    read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
    create_decoded_image(image,&decoded_image,infoheader->biHeight,infoheader->biWidth,4);
    write_file_header(decoded_file,fileheader);
    write_info_header(decoded_file,infoheader);
    write_image_to_decoded_file(decoded_file,decoded_image,infoheader->biHeight,infoheader->biWidth);
    fclose(file);
    fclose(decoded_file);
}*/
