/*
 * list.h the file for the first module of the exercise.
 * Copyright (C) 2022-PRESENT ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */
#ifndef LIST_FILE
#define LIST_FILE
/**
 * @file list.h
 * @author Anna Vasiliou 1070238
 * @brief header list.c file
 * Includes all the function signatures.
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void print_list(FILEHEADER *fileheader, INFOHEADER *infoheader);
int check_file(FILEHEADER *fileheader, INFOHEADER *infoheader);

#endif