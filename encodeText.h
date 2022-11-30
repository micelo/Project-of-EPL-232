/*
 * encodeText.h module 5 header file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */


#ifndef ENCODE_TEXT
#define ENCODE_TEXT
/**
 * @file encodeText.h
 * @author MICHAIL PANAETOV
 * @brief the library for the encodeText.c file
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
#include<time.h>
#include "decodeStegano.h"
#include"header.h"

/**
 * @brief Get the Bit of character table m at position n(nth bit of string m)
 * 
 * @param m string
 * @param n the position to fetch the bit
 * @return int 1 or 0 (depends on the bit)
 */
int getBit(char *m, int n);
/**
 * @brief reading a file and returning the character table of it content
 * 
 * @param f the file to read from
 * @return char* the char table with the file f contents
 */
char* readfile_en(FILE *f);
/**
 * @brief Create a Permutation table out of systemkey for srand() and the size of permutation table
 * 
 * @param N  the size of the permutation table
 * @param systemkey the key to set srand()
 * @return int* the permutation table
 */
int * createPermutationFunction_en(int N,unsigned int systemkey);
/**
 * @brief changes the right most bit of a to the bit b
 * 
 * @param a the integer to set the last bit of
 * @param b the right most bit value
 * @return unsigned int the chaged integer
 */
unsigned int right_bit_change(unsigned int a,unsigned int b);
/**
 * @brief creates the table image with the pixels of the new encrypted image 
 * 
 * @param image table of pixels of the image
 * @param permutation permutation table created from createPermutationFunction_en()
 * @param m the string that is to be encrypted into the image
 * @param height the height of the image
 * @param width the width of the image
 */
void write_text_to_image(PIXEL *** image, int * permutation,char * m,int height,int width);

#endif