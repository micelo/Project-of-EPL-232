#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "header.h"

char * _toBin(int n){
    int c, d, t;
  char *p;

  t = 0;
  p = (char*)malloc(32+1);

  if (p == NULL)
    exit(EXIT_FAILURE);

  for (c = 7 ; c >= 0 ; c--)
  {
    d = n >> c;

    if (d & 1)
      *(p+t) = 1 + '0';
    else
      *(p+t) = 0 + '0';

    t++;
  }
  *(p+t) = '\0';

  return  p;
}

char * _encode(char * _Cov, int bitNum, char * _toHide){
    char * p =(char *)malloc(8 + 1);

    for(int i = 0; i < (8 - bitNum); i++){
        p[i] = _Cov[i];
    }
    for(int i = (8 - bitNum); i < 8 ;i++ ){
        p[i] = _toHide[i - 8 + bitNum];
    }
    p[8] = '\0';
    return p;
}

int _toInt(char * binary){
    int pow = 1;
    int res = 0;
    for(int i = 7; i >=0 ; i--){
        res += pow*(int)(binary[i] - '0');
        pow*=2; 
    }
    
    return res;
}

void write_image_to_encoded_file(FILE * w_file,PIXEL ** encoded_image,int height,int width){
    int padding = ((width*3)%4 == 0) ? 0:1;
    int tmp = 0;
    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){
            fwrite(&(encoded_image[i][j].r),1,1,w_file);
            fwrite(&(encoded_image[i][j].g),1,1,w_file);
            fwrite(&(encoded_image[i][j].b),1,1,w_file);
        }
        if(padding)fwrite(&tmp,3,1,w_file);
    }
    fwrite(&tmp,1,1,w_file);
    fwrite(&tmp,1,1,w_file);
    
}
void write_file_header(FILE * w_file,FILEHEADER * fileheader){
    fwrite(&fileheader->bfType1,1,1,w_file);
    fwrite(&fileheader->bfType2,1,1,w_file);
    fwrite(&fileheader->bfSize,4,1,w_file);
    fwrite(&fileheader->bfReserved1,2,1,w_file);
    fwrite(&fileheader->bfReserved2,2,1,w_file);
    fwrite(&fileheader->bfOffBits,4,1,w_file);
}

void write_info_header(FILE * w_file,INFOHEADER * infoheader){
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


void create_encoded_image(PIXEL *** encoded_image,PIXEL ** cover_image,PIXEL ** toHide_image,int height,int width,int bitNum){
    for(int i = 0 ; i < height;i++){
        for(int j = 0;j < width; j++){
            (*encoded_image)[i][j].r =(dword) _toInt(_encode(_toBin((int)cover_image[i][j].r),bitNum,_toBin((int)toHide_image[i][j].r)));
            (*encoded_image)[i][j].g =(dword) _toInt(_encode(_toBin((int)cover_image[i][j].g),bitNum,_toBin((int)toHide_image[i][j].g)));
            (*encoded_image)[i][j].b =(dword) _toInt(_encode(_toBin((int)cover_image[i][j].b),bitNum,_toBin((int)toHide_image[i][j].b)));
        }
    }

}




int main(){
   // int r = 80; // 0 1 0 1 0 0 0 0 
    //int g = 15; // 0 0 0 0 1 1 1 1
    //int b = 4;
    //printf("r : %s, g : %s, b : %s\n",_toBin(r),_toBin(g),_toBin(b));

    //printf("changed cover : G with lower 4 bits of : R , result ->  %s\n",_encode(_toBin(g),4,_toBin(r)));
    //printf("encoded_binary: %s\n",_encode(_toBin(80),4,_toBin(15)));
    //printf("TO INTEGER FUNCTION CHECK : THE ENCODED INTEGER FROM BEFORE : %d\n",_toInt(_encode(_toBin(g),4,_toBin(r))));

    FILEHEADER * cover_fileheader, * hide_fileheader;
    INFOHEADER * cover_infoheader, * hide_infoheader;
    PIXEL ** cover_image, ** hide_image, ** encoded_image;
    cover_fileheader =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    hide_fileheader  =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    cover_infoheader =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    hide_infoheader  =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * cover_file = fopen("IMG_6865.bmp","r");
    FILE * hide_file  = fopen("IMG_6875.bmp","r");
    FILE * encode_file = fopen("ENCODED_IMAGE.bmp","w+");
    read_file_header(cover_file,&cover_fileheader);
    read_file_header(hide_file,&hide_fileheader);
    read_info_header(cover_file,&cover_infoheader);
    read_info_header(hide_file,&hide_infoheader);
    cover_image = (PIXEL **)malloc((cover_infoheader->biHeight)*sizeof(PIXEL *));
    for(int i = 0 ; i<cover_infoheader->biHeight;i++){
        cover_image[i] = (PIXEL *)malloc(cover_infoheader->biWidth * sizeof(PIXEL));
    }
    hide_image = (PIXEL **)malloc((hide_infoheader->biHeight)*sizeof(PIXEL *));
    for(int i = 0 ; i<hide_infoheader->biHeight;i++){
        hide_image[i] = (PIXEL *)malloc(hide_infoheader->biWidth * sizeof(PIXEL));
    }
    encoded_image = (PIXEL **)malloc((hide_infoheader->biHeight)*sizeof(PIXEL *));
    for(int i = 0 ; i<hide_infoheader->biHeight;i++){
        encoded_image[i] = (PIXEL *)malloc(hide_infoheader->biWidth * sizeof(PIXEL));
    }
    if(hide_infoheader->biHeight != cover_infoheader->biHeight || hide_infoheader->biWidth != cover_infoheader->biWidth){
        printf("NOT THE SAME SIZE\n");
        return 1;
    }
    read_image(cover_file,&cover_image,cover_infoheader->biHeight,cover_infoheader->biWidth);
    read_image(hide_file,&hide_image,hide_infoheader->biHeight,hide_infoheader->biWidth);
    
    create_encoded_image(&encoded_image,cover_image,hide_image,hide_infoheader->biHeight,hide_infoheader->biWidth,4);
    
    write_file_header(encode_file,hide_fileheader);
    write_info_header(encode_file,hide_infoheader);
    write_image_to_encoded_file(encode_file,encoded_image,hide_infoheader->biHeight,hide_infoheader->biWidth);
    fclose(encode_file);
    fclose(cover_file);
    fclose(hide_file);

}