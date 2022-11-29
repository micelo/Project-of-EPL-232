
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int tmp = 0;
void read_file_header(FILE* file,FILEHEADER **fileheader){

  fread(&(*fileheader)->bfType1,1,1,file);
  fread(&(*fileheader)->bfType2,1,1,file);
  fread(&(*fileheader)->bfSize,4,1,file);
  fread(&(*fileheader)->bfReserved1,2,1,file);
  fread(&(*fileheader)->bfReserved2,2,1,file);
  fread(&(*fileheader)->bfOffBits,4,1,file);

}

void read_info_header(FILE *file,INFOHEADER **infoheader){

    fread(&(*infoheader)->biSize,4,1,file);
    fread(&(*infoheader)->biWidth,4,1,file);
    fread(&(*infoheader)->biHeight,4,1,file);
    fread(&(*infoheader)->biPlanes,2,1,file);
    fread(&(*infoheader)->biBitCount,2,1,file);
    fread(&(*infoheader)->biCompression,4,1,file);
    fread(&(*infoheader)->biSizeImage,4,1,file);
    fread(&(*infoheader)->biXPelsPerMeter,4,1,file);
    fread(&(*infoheader)->biYPelsPerMeter,4,1,file);
    fread(&(*infoheader)->biClrUsed,4,1,file);
    fread(&(*infoheader)->biClrImportant,4,1,file);

}

void read_image(FILE *file,PIXEL ***image,int height,int width){

    int padding = ((width*3)%4 == 0) ? 0:1;

    for(int i = 0;i < height;i++){
      for(int j = 0;j < width;j++){
        fread(&((*image)[i][j].r),1,1,file);
        fread(&((*image)[i][j].g),1,1,file);
        fread(&((*image)[i][j].b),1,1,file);
      }
      if(padding)fseek(file,3,SEEK_CUR);
    }
}
