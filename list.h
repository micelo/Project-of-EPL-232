/*
 * client.c the client for using the functions of other libraries for the exercise 4
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */



#ifndef LIST_FILE
#define LIST_FILE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void print_list(FILEHEADER *fileheader, INFOHEADER *infoheader);
int check_file(FILEHEADER *fileheader, INFOHEADER *infoheader);

#endif