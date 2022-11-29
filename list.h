#ifndef LIST_FILE
#define LIST_FILE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void print_list(FILEHEADER *fileheader, INFOHEADER *infoheader);
int check_file(FILEHEADER *fileheader, INFOHEADER *infoheader);

#endif