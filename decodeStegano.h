/*
 * decodeStegano.c the file for the 4th module of the exercise, decoding an image from an image.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef DECODE_STEGANO
#define DECODE_STEGANO
/**
 * @file decodeStegano.h
 * @author Anna Vasiliou 1070238
 * @brief header file for decodeStegano.c file
 * Includes all the function signatures.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "header.h"

char *_toBin(int n);
int _toInt(char *binary);
char *decode(char *binary, int bitNum);
void create_decoded_image(PIXEL **orig_image, PIXEL ***decoded_image, int height, int width, int bitNum);
void write_image_to_decoded_file(FILE *w_file, PIXEL **decoded_image, int height, int width);
void write_file_header(FILE *w_file, FILEHEADER *fileheader);
void write_info_header(FILE *w_file, INFOHEADER *infoheader);

#endif