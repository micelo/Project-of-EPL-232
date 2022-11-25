#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"grayscale_bmp.h"
#include"header.h"

int main(int argc,char ** argv){
    FILEHEADER *fileheader =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER *infoheader =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    if(strcmp(argv[1], "-list") == 0){
        int i = 2;
        while(argv[i] != NULL){
        FILE *file = fopen(argv[i], "r");
        if(file == NULL){
            fprintf(stderr, "ERROR: Can't open file %s\n", argv[2]);
            return 1;
        }
        read_file_header(file,&fileheader);
        read_info_header(file,&infoheader);
        if(check_file(fileheader,infoheader)){
            print_list(fileheader,infoheader);
        }
        i++;
    }
    }
    else if(strcmp(argv[1],"-grayscale") == 0){
        int i = 2;
        while(argv[i]!= NULL){
            char *gray_file_name =(char *)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(gray_file_name,"gray-");
            strcat(gray_file_name,argv[i]);
            printf("gray_file_name : %s\n",gray_file_name);

            FILE *w_file = fopen(gray_file_name,"w+");
            FILE *file = fopen(argv[i],"r");
            if(file == NULL){
                fprintf(stderr, "ERROR: Can't open file %s\n", argv[i]);
                return 1;
            }
            FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
            INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
            
            read_file_header(file,&fileheader);
            read_info_header(file,&infoheader);
            PIXEL **image;
            alloc_image_mem(&image,infoheader->biHeight,infoheader->biWidth);
            read_image(file,&image,infoheader->biHeight,infoheader->biWidth);

            PIXEL **image_grayscale;
            alloc_image_mem(&image_grayscale,infoheader->biHeight,infoheader->biWidth);
            cpy_to_image_grayscale(&image_grayscale,image,infoheader->biHeight,infoheader->biWidth);
            to_grayscale(&image_grayscale,infoheader->biHeight,infoheader->biWidth);
            write_gray_file_header(w_file,fileheader);
            write_gray_info_header(w_file,infoheader);
            write_gray_pixels(w_file,image_grayscale,infoheader->biHeight,infoheader->biWidth);

            fclose(file);
            fclose(w_file);
            

            i++;
        }
    }

return 0;
}