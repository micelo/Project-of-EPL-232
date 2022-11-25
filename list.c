#include "list.h"
#include "header.h"

void print_list(FILEHEADER * fileheader,INFOHEADER * infoheader){
    printf("BITMAP_FILE_HEADER\n");
    printf("==================\n");
    printf("bfType: %c%c\n",fileheader->bfType1,fileheader->bfType2);
    printf("bfSize: %d\n",fileheader->bfSize);
    printf("bfReserved1: %d\n",fileheader->bfReserved1);
    printf("bfReserved2: %d\n",fileheader->bfReserved2);
    printf("bfOffBits: %d\n\n",fileheader->bfOffBits);

    printf("BITMAP_INFO_HEADER\n");
    printf("==================\n");
    printf("biSize: %d\n",infoheader->biSize);
    printf("biWidth: %d\n",infoheader->biWidth);
    printf("biHeight: %d\n",infoheader->biHeight);
    printf("biPlanes: %d\n",infoheader->biPlanes);
    printf("biBitCount: %d\n",infoheader->biBitCount);
    printf("biCompression: %d\n",infoheader->biCompression);
    printf("biSizeImage: %d\n",infoheader->biSizeImage);
    printf("biXPelsPerMeter: %d\n",infoheader->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n",infoheader->biYPelsPerMeter);
    printf("biClrUsed: %d\n",infoheader->biClrUsed);
    printf("biClrImportant: %d\n\n",infoheader->biClrImportant);

    printf("***************************************************************************\n");

}

int check_file(FILEHEADER * fileheader,INFOHEADER * infoheader){

    if(fileheader->bfType1 != 'B' && fileheader->bfType2 != 'M')return 0;
    if(infoheader->biBitCount != 24 || infoheader->biCompression != 0)return 0;

    return 1;
}