#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "header.h"
#include "decodeStegano.h"

char *decrypt_text_from_image(PIXEL **image, int height, int width)
{
    char *text = (char *)malloc(width * height + 1);
    int cnt_of_byte = 0;
    int letter = 0;
    int pow = 128;
    int pos = 0;
    for (int col = 0; col < width; col++)
    {
        for (int row = 0; row < height; row++)
        {
            if (image[row][col].r == 128)
            {
                letter += pow;
                pow /= 2;
            }
            else
            {
                pow /= 2;
            }

            cnt_of_byte++;

            if (cnt_of_byte == 8)
            {

                if (letter == '\0')
                {
                    text[pos] = '\0';
                    return text;
                }
                printf("%c", letter);
                text[pos] = (char)letter;
                pos++;
                pow = 128;
                letter = 0;
                cnt_of_byte = 0;
            }
        }
    }

    return text;
}

#ifdef DEBUG
int main(int argc, char **argv)
{
    FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE *encrypted_image = fopen(argv[1], "r");
    read_file_header(encrypted_image, &fileheader);
    read_info_header(encrypted_image, &infoheader);
    int height = infoheader->biHeight;
    int width = infoheader->biWidth;
    PIXEL **image = (PIXEL **)malloc(height * sizeof(PIXEL *));
    for (int i = 0; i < height; i++)
    {
        image[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
    }
    read_image(encrypted_image, &image, height, width);
    FILE *w_file = fopen("outputText.txt", "w+");
    char *decrypted_text = decrypt_text_from_image(image, height, width);
    // printf("HELLO :\n %s\n",decrypted_text);
}
#endif