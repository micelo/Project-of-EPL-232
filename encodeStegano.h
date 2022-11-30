/*
 * encodeStegano.c the file for the 3th module of the exercise.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

#ifndef ENCODE_STEGANO
#define ENCODE_STEGANO
/**
 * @file encodeStegano.h
 * @author Anna Vasiliou 1070238
 * @brief header file for encodeStegano.c file
 * Includes all the function signatures.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "header.h"

char *_toBin_en(int n);
char *_encode(char *_Cov, int bitNum, char *_toHide);
int _toInt_en(char *binary);
void write_image_to_encoded_file(FILE *w_file, PIXEL **encoded_image, int height, int width);
void write_file_header_en(FILE *w_file, FILEHEADER *fileheader);
void write_info_header_en(FILE *w_file, INFOHEADER *infoheader);
void create_encoded_image(PIXEL ***encoded_image, PIXEL **cover_image, PIXEL **toHide_image, int height, int width, int bitNum);

#endif