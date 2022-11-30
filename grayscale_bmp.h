/*
 * grayscale_bmp.h the file for the 2th module of the exercise.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef GRAYSCALE_FILE
#define GRAYSCALE_FILE
/**
 * @file grayscale_bmp.h
 * @author Anna Vasiliou 1070238
 * @brief header file for grayscale_bmp.c file
 * Includes all the function signatures.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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
