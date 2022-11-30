/*
 * ImageToString.h module 6 header file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef IMAGE_TO_STRING
#define IMAGE_TO_STRING
/**
 * @file ImageToString.h
 * @author MICHAIL PANAETOV
 * @brief the library for ImageToString.c file
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
#include "header.h"
#include "decodeStegano.h"
/**
 * @brief decrypt the text from the image
 * 
 * @param image the image itself(the pixels)
 * @param height the height of the image
 * @param width the width of the image
 * @param outputFile the outputFile where the string will be printed
 * @return char* 
 */
char *decrypt_text_from_image(PIXEL **image, int height, int width,FILE  *outputFile);
#endif