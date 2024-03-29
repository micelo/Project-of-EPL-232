/*
 * stringToImage.c module 7 .c file
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */


/**
 * @file stringToImage.c
 * @author MICHAIL PANAETOV
 * @brief creates an image out of a string
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
#include"header.h"
#include"decodeStegano.h"
/**
 * @brief reads a file and returns it content as a string
 * 
 * @param f the file to read from
 * @return char* the content as a string
 */
char* file_read(FILE *f) {
    long int SIZE_MAX = LONG_MAX;
  if (f == NULL || fseek(f, 0, SEEK_END)) {
    return NULL;
  }

  long length = ftell(f);
  rewind(f);
  if (length == -1 || (unsigned long) length >= SIZE_MAX) {
    return NULL;
  }

  size_t ulength = (size_t) length;
  char *buffer = malloc(ulength + 1);
  if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength) {
    free(buffer);
    return NULL;
  }
  buffer[ulength] = '\0'; // Now buffer points to a string

  return buffer;
}
/**
 * @brief Get the Bit of character table m at position n(nth bit of string m)
 * 
 * @param m string
 * @param n the position to fetch the bit
 * @return int 1 or 0 (depends on the bit)
 */
int _getBit(char *m, int n){
          if(n < 0 && n > (8*strlen(m))){
            printf("FAILED TO RETRIEVE THE BYTE NEEDED!\n");
            return -1;
          }
          int _textByte = n/8;
          int _bitOfByte = floor(7 - n%8);

          char c = m[_textByte];
          char bits[8];
          for (int i = 0; i < 8; i++)
          {
             bits[i] = (c >> i) & 1;
          }
    return (int)(bits[_bitOfByte]);    
}
/**
 * @brief Create a image with encoded text 
 * 
 * @param image image 
 * @param text the text
 * @param height height of the image
 * @param width width of the image
 */
void create_image_with_encoded_text(PIXEL ***image, char * text,int height,int width){
    int cnt=0;
    for(int j=0;j<width;j++){
        for(int i = 0;i<height;i++){
            if(cnt == (strlen(text)*8+9))break;
            if(_getBit(text,cnt) == 1){
                (*image)[i][j].r = 128;
                (*image)[i][j].g = 128;
                (*image)[i][j].b = 128;
            }
            else{
                (*image)[i][j].r = (*image)[i][j].g = (*image)[i][j].b = 0;
            }
            cnt++;
        }
    }

        for(int i = 0 ; i < width;i++){
            for(int j = 0 ; j < height;j++){
                if(i*height + j >= cnt){
                    (*image)[j][i].r = (*image)[j][i].g = (*image)[j][i].b = 0;
                }
            }
        }


}

#ifdef DEBUG
int main(int argc, char **argv){
    FILEHEADER * fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * file = fopen(argv[2],"r");
    read_file_header(file,&fileheader);
    read_info_header(file,&infoheader);
    int height = infoheader->biHeight;
    int width =  infoheader->biWidth;
    FILE * file_text = fopen(argv[3],"r");
    char * text = file_read(file_text);
    PIXEL ** image = (PIXEL **)malloc(height*sizeof(PIXEL *));
    for(int i = 0 ; i < height;i++){
        image[i] = (PIXEL *)calloc(sizeof(PIXEL),width);
    }
    create_image_with_encoded_text(&image,text,height,width);
    char * new_file_name = (char *)malloc(strlen("encryptedTextImage.bmp") + 1);
    strcpy(new_file_name,"encryptedTextImage.bmp\0");
    FILE * encrypted_image = fopen("DECODED_IMAGE.bmp", "w+");
    write_file_header(encrypted_image,fileheader);
    write_info_header(encrypted_image,infoheader);
    write_image_to_decoded_file(encrypted_image,image,height,width);
    fclose(encrypted_image);
}
#endif