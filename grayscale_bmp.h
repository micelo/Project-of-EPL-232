/*
 * client.c the client for using the functions of other libraries for the exercise 4
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef GRAYSCALE_FILE
#define GRAYSCALE_FILE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "header.h"

void to_grayscale(PIXEL ***image_grayscale, int height, int width);
void cpy_to_image_grayscale(PIXEL ***image_grayscale, PIXEL **image, int height, int width);
void alloc_image_mem(PIXEL ***image_grayscale, int height, int width);
void free_image_mem(PIXEL ***image_grayscale, int height, int width);
void write_gray_info_header(FILE *w_file, INFOHEADER *infoheader);
void write_gray_file_header(FILE *w_file, FILEHEADER *fileheader);
void write_gray_pixels(FILE *w_file, PIXEL **image_grayscale, int height, int width);

#endif
