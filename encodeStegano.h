#ifndef ENCODE_STEGANO
#define ENCODE_STEGANO

#include "header.h"

char *_toBin_en(int n);
char *_encode(char *_Cov, int bitNum, char *_toHide);
int _toInt_en(char *binary);
void write_image_to_encoded_file(FILE *w_file, PIXEL **encoded_image, int height, int width);
void write_file_header_en(FILE *w_file, FILEHEADER *fileheader);
void write_info_header_en(FILE *w_file, INFOHEADER *infoheader);
void create_encoded_image(PIXEL ***encoded_image, PIXEL **cover_image, PIXEL **toHide_image, int height, int width, int bitNum);

#endif