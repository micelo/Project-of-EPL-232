#ifndef DECODE_STEGANO
#define DECODE_STEGANO
#include "header.h"


char * _toBin(int n);
int _toInt(char * binary);
char * decode(char * binary, int bitNum);
void create_decoded_image(PIXEL **orig_image,PIXEL ***decoded_image,int height,int width,int bitNum);
void write_image_to_decoded_file(FILE * w_file,PIXEL ** decoded_image,int height,int width);
void write_file_header(FILE * w_file,FILEHEADER * fileheader);
void write_info_header(FILE * w_file,INFOHEADER * infoheader);


#endif