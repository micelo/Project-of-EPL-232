
/*
 * decodeText.c module 6 .c file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */


/**
 * @file decodeText.c
 * @author Michail Panaetov
 * @brief DECODING THE TEXT FROM AN ENCODED IMAGE FILE (BMP) THAT WAS ENCODED TO IT USING -encodeText option
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
#include "header.h"
#include "decodeText.h"
/**
 * @brief reads a file and stores it as a unique string
 * 
 * @param f FILE TO BE READ FROM
 * @return char* WHOLE TEXT OF THE FILE f
 */
char *readfile(FILE *f)
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
 * @brief Create a Permutation Function out of rand() switches between a f(x) = x function where f: N->N
 * 
 * @param N the length of the permutation table
 * @param systemkey the systemkey to be used
 * @return int* the permutation table
 */
int *createPermutationFunction(int N, unsigned int systemkey)
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
 * @brief Create a string from image object
 * 
 * @param image the image content (pixels)
 * @param N the size of the string (MAX_LENGTH)
 * @param permutation the permutation table that was created from createPermutationFunction()
 * @param height the height of the image 
 * @param width the width of the image
 * @param until until where to find letters in image
 * @return char* the text created from image
 */
char *create_string_from_image(PIXEL **image, int N, int *permutation, int height, int width, int until)
{
  int l = 0;
  int pow = 0;
  int o = 0;
  char *res = (char *)malloc(N);
  int cnt = 0;
  for (int i = 0; i <= N && i < (height * width) * 3 && i <= until; i += 8)
  {
    pow = 128;
    l = 0;
    for (int j = 0; j < 8; j++)
    {
      o = permutation[i + j];
      int x = o / (width * 3);
      int y = o % (width * 3) / 3;
      int rgb = o % 3;
      if (rgb == 0)
      {
        l += pow * (image[x][y].r % 2 == 0 ? 0 : 1);
      }
      else if (rgb == 1)
      {

        l += pow * (image[x][y].g % 2 == 0 ? 0 : 1);
      }
      else if (rgb == 2)
      {

        l += pow * (image[x][y].b % 2 == 0 ? 0 : 1);
      }

      pow /= 2;
    }

    res[cnt] = l;
    cnt++;
    if (l == '\0')
      break;
  }
  return res;
}

#ifdef DEBUG
int main(int argc, char **argv)
{
  FILE *file = fopen("encrypted_bmp.bmp", "r");
  PIXEL **image;
  FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
  INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));

  read_file_header(file, &fileheader);
  read_info_header(file, &infoheader);
  int height = infoheader->biHeight;
  int width = infoheader->biWidth;
  image = (PIXEL **)malloc((infoheader->biHeight) * sizeof(PIXEL *));
  for (int i = 0; i < infoheader->biHeight; i++)
  {
    image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
  }

  read_image(file, &image, infoheader->biHeight, infoheader->biWidth);
  int *permutation = createPermutationFunction(height * width * 3, (unsigned int)0);
  create_string_from_image(image, height * width * 3, permutation, infoheader->biHeight, infoheader->biWidth);

  return 0;
}
#endif
