/*
 * encodeText.c module 5 .c file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

/**
 * @file encodeText.c
 * @author MICHAIL PANAETOV
 * @brief encoding text into an image
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "decodeStegano.h"
#include "header.h"
/**
 * @brief reading a file and returning the character table of it content
 * 
 * @param f the file to read from
 * @return char* the char table with the file f contents
 */
char *readfile_en(FILE *f)
{
  long int SIZE_MAX = LONG_MAX;
  if (f == NULL || fseek(f, 0, SEEK_END))
  {
    return NULL;
  }

  long length = ftell(f);
  rewind(f);
  if (length == -1 || (unsigned long)length >= SIZE_MAX)
  {
    return NULL;
  }

  size_t ulength = (size_t)length;
  char *buffer = malloc(ulength + 1);
  if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength)
  {
    free(buffer);
    return NULL;
  }
  buffer[ulength] = '\0'; // Now buffer points to a string

  return buffer;
}
/**
 * @brief Get the Bit of character table m at position n(nth bit of string m)
 * 
 * @param m string
 * @param n the position to fetch the bit
 * @return int 1 or 0 (depends on the bit)
 */
int getBit(char *m, int n)
{
  if (n < 0 && n > (8 * strlen(m)))
  {
    printf("FAILED TO RETRIEVE THE BYTE NEEDED!\n");
    return -1;
  }
  int _textByte = n / 8;
  int _bitOfByte = floor(7 - n % 8);

  char c = m[_textByte];
  char bits[8];
  for (int i = 0; i < 8; i++)
  {
    bits[i] = (c >> i) & 1;
  }
  return (int)(bits[_bitOfByte]);
}
/**
 * @brief Create a Permutation table out of systemkey for srand() and the size of permutation table
 * 
 * @param N  the size of the permutation table
 * @param systemkey the key to set srand()
 * @return int* the permutation table
 */
int *createPermutationFunction_en(int N, unsigned int systemkey)
{
  srand(systemkey);
  int *permutation = malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++)
  {
    permutation[i] = i;
  }
  for (int i = 0; i < N; i++)
  {
    int left = rand() % (N - 1);
    int right = rand() % (N - 1);
    int temp = permutation[right];
    permutation[right] = permutation[left];
    permutation[left] = temp;
  }

  return permutation;
}
/**
 * @brief changes the right most bit of a to the bit b
 * 
 * @param a the integer to set the last bit of
 * @param b the right most bit value
 * @return unsigned int the chaged integer
 */
unsigned int right_bit_change(unsigned int a, unsigned int b)
{

  return (a & 254) | b;
}
/**
 * @brief creates the table image with the pixels of the new encrypted image 
 * 
 * @param image table of pixels of the image
 * @param permutation permutation table created from createPermutationFunction_en()
 * @param m the string that is to be encrypted into the image
 * @param height the height of the image
 * @param width the width of the image
 */
void write_text_to_image(PIXEL ***image, int *permutation, char *m, int height, int width)
{
  for (int i = 0; i < (1 + strlen(m)) * 8 && i < height * width * 3; i++)
  {

    int b = getBit(m, i);
    int o = permutation[i];
    int x = o / (width * 3);
    int y = o % (width * 3) / 3;
    int rgb = o % 3;
    if (rgb == 0)
    {
      (*image)[x][y].r = right_bit_change((*image)[x][y].r, (unsigned int)b);
    }
    else if (rgb == 1)
    {
      (*image)[x][y].g = right_bit_change((*image)[x][y].g, (unsigned int)b);
    }
    else if (rgb == 2)
    {
      (*image)[x][y].b = right_bit_change((*image)[x][y].b, (unsigned int)b);
    }
  }
}
#ifdef DEBUG
int main()
{

  FILE *file = fopen("testing.bmp", "r");
  FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
  INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));

  read_file_header(file, &fileheader);
  read_info_header(file, &infoheader);

  int width = infoheader->biWidth;
  int height = infoheader->biHeight;
  PIXEL **image = (PIXEL **)malloc(sizeof(PIXEL *) * height);
  for (int i = 0; i < height; i++)
  {
    image[i] = (PIXEL *)malloc(sizeof(PIXEL) * width);
  }
  read_image(file, &image, height, width);
  char *secret = readfile(fopen("secret.txt", "r"));
  int length = strlen(secret) + 1;
  if (length * 8 >= infoheader->biHeight * infoheader->biWidth * 3)
    length = infoheader->biHeight * infoheader->biWidth;
  printf("the length is : %d\n", length);
  int *permutation = createPermutationFunction(height * width * 3, (unsigned int)0);
  //  printf("THE PERMUTATIONS ARE: \n");
  //  for(int i = 0; i < 66;i++){
  //   printf("%d ",permutation[i]);
  //  }
  write_text_to_image(&image, permutation, secret, height, width);
  FILE *w_file = fopen("encrypted_bmp.bmp", "w+");
  write_file_header(w_file, fileheader);
  write_info_header(w_file, infoheader);
  write_image_to_decoded_file(w_file, image, height, width);
  return 0;
}

#endif