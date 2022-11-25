
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
/*oid write_gray_file_header(FILE * w_file,FILEHEADER * fileheader){
    fwrite(&fileheader->bfType1,1,1,w_file);
    fwrite(&fileheader->bfType2,1,1,w_file);
    fwrite(&fileheader->bfSize,4,1,w_file);
    fwrite(&fileheader->bfReserved1,2,1,w_file);
    fwrite(&fileheader->bfReserved2,2,1,w_file);
    fwrite(&fileheader->bfOffBits,4,1,w_file);
}*/
/*void write_gray_info_header(FILE * w_file,INFOHEADER * infoheader){
    fwrite(&infoheader->biSize,4,1,w_file);
    fwrite(&infoheader->biWidth,4,1,w_file);
    fwrite(&infoheader->biHeight,4,1,w_file);
    fwrite(&infoheader->biPlanes,2,1,w_file);
    fwrite(&infoheader->biBitCount,2,1,w_file);
    fwrite(&infoheader->biCompression,4,1,w_file);
    fwrite(&infoheader->biSizeImage,4,1,w_file);
    fwrite(&infoheader->biXPelsPerMeter,4,1,w_file);
    fwrite(&infoheader->biYPelsPerMeter,4,1,w_file);
    fwrite(&infoheader->biClrUsed,4,1,w_file);
    fwrite(&infoheader->biClrImportant,4,1,w_file);

}
void write_gray_pixels(FILE * w_file,PIXEL **image,int height,int width){
    int padding = ((width*3)%4 == 0) ? 0:1;
    for(int i = 0 ;i < height;i++){
        for(int j = 0;j < width;j++){
            fwrite(&image[i][j].r,1,1,w_file);
            fwrite(&image[i][j].g,1,1,w_file);
            fwrite(&image[i][j].b,1,1,w_file);

        }
        int tmp = 0;
        if(padding)fwrite(&tmp,3,1,w_file);
    }
    fwrite(&tmp,1,1,w_file);
    fwrite(&tmp,1,1,w_file);
    fclose(w_file);
}*/
/*
int main(){

  return 0;
}*/
/*
int main(){
  FILE * file = fopen("4x3.bmp","r");
  FILE * gray_file = fopen("4x3_gray.bmp", "w+");

  FILEHEADER *fileheader =(FILEHEADER *)malloc(sizeof(FILEHEADER));
  read_file_header(file,&fileheader);
  INFOHEADER *infoheader =(INFOHEADER *)malloc(sizeof(INFOHEADER));

  printf("bfType1: %c\nbfType2 : %c\n",fileheader->bfType1,fileheader->bfType2);
  printf("bfSize: %d\n",fileheader->bfSize);
  printf("bfReserved1 : %d\nbfReserved2 : %d\nbfOffBits : %d\n",fileheader->bfReserved1,fileheader->bfReserved2,fileheader->bfOffBits);

  read_info_header(file,&infoheader);
  printf("INFO HEADER : \n SIZE: %d \n WIDTH : %d \nHEIGHT : %d\n IMAGE SIZE: %d\n",infoheader->biSize,infoheader->biWidth,infoheader->biHeight,infoheader->biSizeImage);

  PIXEL **image =(PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
  for(int i = 0 ; i < infoheader->biHeight;i++){
    image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
  }
  read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
    printf("\n");
  //GRAYSCALE 
  for(int i = 0 ; i < infoheader->biHeight;i++){

    for(int j = 0 ;j < infoheader->biWidth;j++){
        int cnt = 0 ;
        image[i][j].r = roundf(image[i][j].r * 0.299);
        image[i][j].g = roundf(image[i][j].g * 0.587);
        image[i][j].b = roundf(image[i][j].b * 0.114);
        cnt += image[i][j].r + image[i][j].g + image[i][j].b;
        image[i][j].r = image[i][j].b = image[i][j].g = cnt;
    }
  }
    fclose(file);
    write_gray_file_header(gray_file,fileheader);
    write_gray_info_header(gray_file,infoheader);
    write_gray_pixels(gray_file,image,infoheader->biHeight,infoheader->biWidth);

    print_list(fileheader,infoheader);

    printf("HELLO WORLD!");

    return 0;

    






}
*/