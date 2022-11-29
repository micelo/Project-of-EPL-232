
#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define BYTES_PER_PIXEL 3
//#define FILE_HEADER_SIZE 14;
// const int INFO_HEADER_SIZE = 40;

typedef unsigned char byte;
typedef unsigned short int word; // 16 bits = 2 bytes
typedef unsigned int dword;      //  32 bits = 4 bytes

typedef struct
{
  byte bfType1;     // 1 byte
  byte bfType2;     // 1 byte
  dword bfSize;     // 4 bytes
  word bfReserved1; // don't need it
  word bfReserved2; // don't need it
  dword bfOffBits;  // don't need it

} FILEHEADER;

typedef struct
{
  dword biSize;          // 4 bytes
  dword biWidth;         // 4 bytes
  dword biHeight;        // 4 bytes
  word biPlanes;         // don't need it
  word biBitCount;       // 2 bytes
  dword biCompression;   // 4 bytes
  dword biSizeImage;     // 4 bytes
  dword biXPelsPerMeter; // don't need it
  dword biYPelsPerMeter; // don't need it
  dword biClrUsed;       // don't need it
  dword biClrImportant;  // don't need it

} INFOHEADER;

typedef struct
{
  dword r;
  dword g;
  dword b;

} PIXEL;

void read_file_header(FILE *file, FILEHEADER **fileheader);
void read_info_header(FILE *file, INFOHEADER **infoheader);
void read_image(FILE *file, PIXEL ***image, int height, int width);
void write_gray_file_header(FILE *file, FILEHEADER *fileheader);
void write_gray_info_header(FILE *w_file, INFOHEADER *infoheader);
void write_gray_pixels(FILE *w_file, PIXEL **image, int height, int width);
void print_list(FILEHEADER *fileheader, INFOHEADER *infoheader);

#endif