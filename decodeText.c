
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<time.h>
#include"header.h"



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
  
      srand(systemkey);
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
  for(int i = 0 ;i < N && i < (height * width)*3;i+=8){
      pow = 128;
      l=0;
      for(int j = 0; j < 8;j++){
        o = permutation[i+j];
        int x = o /(width*3);
        int y = o %(width*3) / 3;
      
        int rgb = o % 3; 
        if(rgb == 0)
        { 
            l += pow * ( image[x][y].r%2 == 0 ? 0:1);
            
        }
        else if(rgb == 1){
      
          l += pow * ( image[x][y].g%2 == 0 ? 0:1);
        }
        else if( rgb == 2){
         
          l += pow * ( image[x][y].b%2 == 0? 0:1);
        }

        pow/=2;
      }
      if(l == '\0')break;
      
      printf("%c",l);
      

  }


}

#ifdef DEBUG
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
    create_string_from_image(image,height*width*3,permutation,infoheader->biHeight,infoheader->biWidth);

    
    return 0;
        
}
#endif

