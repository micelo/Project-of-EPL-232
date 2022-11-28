
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"header.h"
#include<limits.h>
#include<math.h>
#include<time.h>

/////////////////////////////////
typedef unsigned char byte;
typedef unsigned short int word; // 16 bits = 2 bytes
typedef unsigned int dword; //  32 bits = 4 bytes

typedef struct {
  byte bfType1; // 1 byte
  byte bfType2; // 1 byte
  dword bfSize; // 4 bytes
  word bfReserved1; // don't need it
  word bfReserved2; // don't need it
  dword bfOffBits; // don't need it


}FILEHEADER;

typedef struct{
  dword biSize; // 4 bytes
  dword biWidth; // 4 bytes
  dword biHeight; // 4 bytes
  word biPlanes; // don't need it
  word biBitCount; // 2 bytes
  dword biCompression; // 4 bytes
  dword biSizeImage; // 4 bytes
  dword biXPelsPerMeter; // don't need it
  dword biYPelsPerMeter; // don't need it
  dword biClrUsed; // don't need it
  dword biClrImportant; // don't need it

}INFOHEADER;

 typedef struct{
   dword r;
   dword g;
   dword b;

 }PIXEL;
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



















//////////////////////////////////////

char* readfile(FILE *f) {
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

int getBit(char *m, int n){
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

int * createPermutationFunction(int N,unsigned int systemkey){
  
      srand(77);
    int * permutation = malloc(sizeof(int) * N);
    for(int i = 0 ; i < N;i++){
        permutation[i] = i;
    }
    for(int i = 0 ; i < N;i++){
      int left = rand()%(N-1);
      int right = rand()%(N-1);
      int temp = permutation[right];
      permutation[right] = permutation[left];
      permutation[left] = temp;
    }

    return permutation;
}

unsigned int right_bit_change(unsigned int a,unsigned int b){
  return (a & 254) | b;
}

void create_string_from_image(PIXEL **image,int N,int * permutation,int height,int width){
  int l = 0;
  int pow = 0;
  int o = 0;
  for(int i = 0 ;i < N && i < (height * width - 1)*8;i+=8){
      pow = 128;
      l=0;
      for(int j = 0; j < 8;j++){
        o = permutation[i+j];
        int x = o /(width*3);
        int y = o %(width*3) / 3;
      
        int rgb = o % 3; //// 
        if(rgb == 0)
        { 
          //printf("THE BIT OF THE LETTER : %d\n",(image[x][y].r%2 == 0 ? 0:1));
            l += pow * ( image[x][y].r%2 == 0 ? 0:1);
            
        }
        else if(rgb == 1){
         // printf("THE BIT OF THE LETTER : %d\n",(image[x][y].g%2 == 0 ? 0:1));
          l += pow * ( image[x][y].g%2 == 0 ? 0:1);
        }
        else if( rgb == 2){
         // printf("THE BIT OF THE LETTER : %d\n",(image[x][y].b%2 == 0 ? 0:1));
          l += pow * ( image[x][y].b%2 == 0? 0:1);
        }

        pow/=2;
      }
      if(l == '\0')break;
      
      printf("%c",l);
      

  }


}

int main(int argc,char ** argv){
    FILE *file = fopen("encrypted_bmp.bmp","r");
    PIXEL ** image;
    FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    
    read_file_header(file,&fileheader);
    read_info_header(file,&infoheader);
    int height = infoheader->biHeight;
    int width = infoheader->biWidth;
     image = (PIXEL **)malloc((infoheader->biHeight)*sizeof(PIXEL *));
    for(int i = 0 ; i<infoheader->biHeight;i++){
        image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
    }
    
    read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
    int * permutation = createPermutationFunction(height*width*3,(unsigned int)0);
    // printf("THE PERMUTATIONS ARE: \n");
    // for(int i = 0 ; i < 66;i++){
    //     printf("%d ",permutation[i]);
    // }
    // printf("\n");
    create_string_from_image(image,height*width*3,permutation,infoheader->biHeight,infoheader->biWidth);

    
    return 0;
        
}


