/*
 * decodeText.h module 6 header file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef DECODE_TEXT
#define DECODE_TEXT
/**
 * @file decodeText.h
 * @author MICHAIL PANAETOV
 * @brief THIS IS THE LIBRARY FOR THE decodeText.c
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "header.h"
/**
 * @brief reads the file f and returns it content
 * 
 * @param f the character table with all the characters of the file
 * @return char* 
 */
char *readfile(FILE *f);
/**
 * @brief Create a Permutation Function out of rand() switches between a f(x) = x function where f: N->N
 * 
 * @param N the length of the permutation table
 * @param systemkey the systemkey to be used
 * @return int* the permutation table
 */
int *createPermutationFunction(int N, unsigned int systemkey);
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
char *create_string_from_image(PIXEL **image, int N, int *permutation, int height, int width, int until);

#endif