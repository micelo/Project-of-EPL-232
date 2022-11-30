/*
 * stringToImage.h module 7 header file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */



#ifndef STRING_TO_IMAGE
#define STRING_TO_IMAGE
/**
 * @file stringToImage.h
 * @author MICHAIL PANAETOV
 * @brief stringToImage.c library (header file)
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @file stringToImage.h
 * @author MICHAIL PANAETOV
 * @brief the library for the stringToImage.c file
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include"header.h"
#include"decodeStegano.h"


/**
 * @brief reads a file and returns it content as a string
 * 
 * @param f the file to read from
 * @return char* the content as a string
 */
char* file_read(FILE *f);
/**
 * @brief Get the Bit of character table m at position n(nth bit of string m)
 * 
 * @param m string
 * @param n the position to fetch the bit
 * @return int 1 or 0 (depends on the bit)
 */
int _getBit(char *m, int n);
/**
 * @brief Create a image with encoded text 
 * 
 * @param image image 
 * @param text the text
 * @param height height of the image
 * @param width width of the image
 */
void create_image_with_encoded_text(PIXEL ***image, char * text,int height,int width);

#endif