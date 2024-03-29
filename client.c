/*
 * client.c the client for using the functions of other libraries for the exercise 4
 * Copyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING.
 */

/**
 * @file client.c
 * @author Michail Panaetov 1314594, Anna Vasiliou 1070238
 * @brief This is the client. This file gets the name of each module from command
 * line and calls the according functions. It includes all the headers of each module.
 * @version 0.1
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 * @bug no known bugs
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"grayscale_bmp.h"
#include"header.h"
#include"encodeStegano.h"
#include"decodeStegano.h"
#include"encodeText.h"
#include"decodeText.h"
#include"ImageToString.h"
#include"stringToImage.h"



/**
 * @brief Main method for comparing the arguments given to the names of the modules and
 * calling the according functions.
 * Firstly, allocates memory for the fileheader and the infoheader structure pointers.
 *
 * For the list module: Checks the argument and if it matches it opens a file that contains the bmp image
 * (makes the according checks) and then reads the info and file header of the image and prints these
 * information as a list. 
 * 
 * For the grayscale module: Checks the argument and if it matches it opens a file that contains the bmp image
 * (makes the according checks) and then reads the info and file header of the image. Then it calls the according
 * function to change the image information and make it black and white (explained in the grayscale.c file).
 * 
 * For the encodeStegano module: Checks the argument and if it matches it opens two files that contain the two bmp images
 * (the cover and the hiden image). Then it reads the info and file header of each image and makes the according bit
 * combination calling the corresponding function (explained in the encodeStegano.c file).
 * 
 * For the decodeStegano module: Checks the argument and if it matches it opens a file that contains the image that 
 * will be decoded. Then it reads the info and file header of this image and makes the corresponding functions to
 * reveal the hiden image.
 * 
 * For the encodeText module: Checks the argument and if it matches it opens two files that contain the text that will be
 * encoded and the image that will contain the text. Then it reads the info and file header of the image and using the 
 * according permutation function it encodes text in the image (functions explained in the encodeText.c file)
 *
 * For the decodeTest module: Checks the argument and if it matches it opens a file that contains the bmp image that
 * has a hidden message. By reading the file and info header of the bmp image, and using the other permutation function,
 * it decodes the text hidden in the bmp image.
 * 
 * For the StringToImage module: Checks the argument and if it matches it opens a file that contains the sample image 
 * and the String that is going to be transformed into an image. Then it calls the according functions to do so (explained
 * int the StringToImage.c file).
 * 
 * For the ImageToString module: Checks the argument and if it matches it opens a file that contains the image that
 * is going to be encrypted. Then it calls the according functions to return the text (explained int the ImageToString.c file)
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return int
 */
int main(int argc,char ** argv){
    FILEHEADER *fileheader =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER *infoheader =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    if(argc < 3){
        printf("*******************************\nclient.c the client for using the functions of other libraries for the exercise 4\nCopyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU\n");
 printf("This is free software; you can redistribute it and/or\nmodify it under the terms of the GNU General Public\nLicense, see the file COPYING.\n*******************************\n");
        printf("TOO FEW COMMAND LINE ARGUMENTS \n");
        return 1;
    }
    if(strcmp(argv[1], "-list") == 0){
        if(argc < 3){
            printf("*******************************\nclient.c the client for using the functions of other libraries for the exercise 4\nCopyright (C) 2022-PRESENT MICHAIL PANAETOV & ANNA VASILIOU\n");
 printf("This is free software; you can redistribute it and/or\nmodify it under the terms of the GNU General Public\nLicense, see the file COPYING.\n*******************************\n");
            printf("FILES NOT GIVEN \n");
            return 1;
        }
        int i = 2;
        while(argv[i] != NULL){
        
        FILE *file = fopen(argv[i], "r");
        if(file == NULL){
            fprintf(stderr, "ERROR: Can't open file %s\n", argv[2]);
            i++;
            continue;
        }
        read_file_header(file,&fileheader);
        read_info_header(file,&infoheader);
        if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            i++;
            continue;
        }
         if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                i++;
                continue;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                i++;
                continue;
            }
        if(check_file(fileheader,infoheader)){
            print_list(fileheader,infoheader);
        }
        i++;
    }
    }
    else if (strcmp(argv[1], "-grayscale") == 0)
    {
        int i = 2;
        if (argc < 3)
        {
            printf("FILES NOT GIVEN \n");
            return 1;
        }
        while (argv[i] != NULL)
        {
            char *gray_file_name = (char *)malloc((strlen(argv[i]) + 5) * sizeof(char));
            strcpy(gray_file_name, "gray-");
            strcat(gray_file_name, argv[i]);
            printf("gray_file_name : %s\n", gray_file_name);

            FILE *w_file = fopen(gray_file_name, "w+");
            FILE *file = fopen(argv[i], "r");
            if (file == NULL)
            {
                fprintf(stderr, "ERROR: Can't open file %s\n", argv[i]);
                return 1;
            }

            FILEHEADER *fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
            INFOHEADER *infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
            
            read_file_header(file,&fileheader);
            read_info_header(file,&infoheader);
            if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
            if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                i++;
                continue;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                i++;
                continue;
            }
            PIXEL **image;
            alloc_image_mem(&image, infoheader->biHeight, infoheader->biWidth);
            read_image(file, &image, infoheader->biHeight, infoheader->biWidth);

            PIXEL **image_grayscale;
            alloc_image_mem(&image_grayscale, infoheader->biHeight, infoheader->biWidth);
            cpy_to_image_grayscale(&image_grayscale, image, infoheader->biHeight, infoheader->biWidth);
            to_grayscale(&image_grayscale, infoheader->biHeight, infoheader->biWidth);
            write_gray_file_header(w_file, fileheader);
            write_gray_info_header(w_file, infoheader);
            write_gray_pixels(w_file, image_grayscale, infoheader->biHeight, infoheader->biWidth);

            fclose(file);
            fclose(w_file);

            i++;
        }
    }
    else if (strcmp(argv[1], "-encodeStegano") == 0)
    {

        int bitNum = (int)argv[2][0] -'0';
        FILEHEADER * cover_fileheader, * hide_fileheader;
    INFOHEADER * cover_infoheader, * hide_infoheader;
    PIXEL ** cover_image, ** hide_image, ** encoded_image;
    cover_fileheader =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    hide_fileheader  =(FILEHEADER *)malloc(sizeof(FILEHEADER));
    cover_infoheader =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    hide_infoheader  =(INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * cover_file = fopen(argv[3],"r");
    FILE * hide_file  = fopen(argv[4],"r");
    char * encoded_file_name =(char *)malloc((strlen(argv[3]) + 4) * sizeof(char));
    strcpy(encoded_file_name,"new-");
    strcat(encoded_file_name,argv[3]);
    FILE * encode_file = fopen(encoded_file_name,"w+");
    read_file_header(cover_file,&cover_fileheader);
    read_file_header(hide_file,&hide_fileheader);
    read_info_header(cover_file,&cover_infoheader);
    read_info_header(hide_file,&hide_infoheader);
    if(cover_fileheader->bfType1 != 'B' || cover_fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
        if(hide_fileheader->bfType1 != 'B' || hide_fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
     if(cover_infoheader->biCompression == 1 || hide_infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(cover_infoheader->biBitCount != 24 || hide_infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
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
        printf("ERROR: THE COVER AND THE HIDE IMAGES:NOT THE SAME SIZE\n");
        return 1;
    }
    read_image(cover_file,&cover_image,cover_infoheader->biHeight,cover_infoheader->biWidth);
    read_image(hide_file,&hide_image,hide_infoheader->biHeight,hide_infoheader->biWidth);
    
    create_encoded_image(&encoded_image,cover_image,hide_image,hide_infoheader->biHeight,hide_infoheader->biWidth,bitNum);
    
    write_file_header(encode_file,hide_fileheader);
    write_info_header(encode_file,hide_infoheader);
    write_image_to_encoded_file(encode_file,encoded_image,hide_infoheader->biHeight,hide_infoheader->biWidth);
    fclose(encode_file);
    fclose(cover_file);
    fclose(hide_file);


    }
    else if(strcmp(argv[1],"-decodeStegano") == 0){
    int bitNum = (int)argv[2][0] -'0';
    FILEHEADER * fileheader = (FILEHEADER * )malloc(sizeof(FILEHEADER));
    INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * file = fopen(argv[3], "r");
    char * decoded_file_name =(char *)malloc((strlen(argv[3]) + 4) * sizeof(char));
    strcpy(decoded_file_name,"new-");
    strcat(decoded_file_name,argv[3]);
    FILE * decoded_file = fopen(decoded_file_name, "w+");
    read_file_header(file,&fileheader);
    read_info_header(file,&infoheader);
    if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
     if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
    PIXEL ** image, **decoded_image;
    image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
    decoded_image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
    for(int i = 0 ; i < infoheader->biHeight;i++){
        image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
        decoded_image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
    }
    read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
    create_decoded_image(image,&decoded_image,infoheader->biHeight,infoheader->biWidth,bitNum);
    write_file_header(decoded_file,fileheader);
    write_info_header(decoded_file,infoheader);
    write_image_to_decoded_file(decoded_file,decoded_image,infoheader->biHeight,infoheader->biWidth);
    fclose(file);
    fclose(decoded_file);

    }
    else if (strcmp(argv[1], "-encodeText") == 0)
    {

            FILEHEADER * fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
            INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
            FILE * file = fopen(argv[2],"r");
            FILE * secret_text = fopen(argv[3],"r");
            read_file_header(file,&fileheader);
            read_info_header(file,&infoheader);
            if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
             if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
            PIXEL ** image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
            for(int i = 0 ; i < infoheader->biHeight;i++){
                image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
            }
            read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
            char * secret = readfile(secret_text);
            int length = strlen(secret);
            if(length * 8 > infoheader->biHeight * infoheader->biWidth * 3){
                length = infoheader->biHeight * infoheader->biWidth*3;
            }
            int * permutation = createPermutationFunction_en(infoheader->biHeight*infoheader->biWidth*3,(unsigned int)0);
            char * encoded_file_name = (char *)malloc(strlen(argv[2])+ 5);
            strcpy(encoded_file_name,"new-");
            strcat(encoded_file_name,argv[2]);
            FILE * w_file = fopen(encoded_file_name,"w+");
            write_file_header(w_file,fileheader);
            write_info_header(w_file,infoheader);
            PIXEL ** new_image = (PIXEL **)malloc(infoheader->biHeight*sizeof(PIXEL *));
            for(int i = 0 ; i < infoheader->biHeight;i++){
                new_image[i] =(PIXEL *)malloc(infoheader->biWidth*sizeof(PIXEL));
            }

        write_text_to_image(&image, permutation, secret, infoheader->biHeight, infoheader->biWidth);
        write_image_to_decoded_file(w_file, image, infoheader->biHeight, infoheader->biWidth);
        fclose(w_file);
        free(secret);
        free(image);
    }
    else if(strcmp(argv[1],"-decodeText") == 0){
         FILEHEADER * fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
         INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
         FILE * file = fopen(argv[2],"r");
         int length_of_secret = atoi(argv[3]);
         FILE * w_file = fopen(argv[4],"w+");
         read_file_header(file,&fileheader);
         read_info_header(file,&infoheader);
         if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
          if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
         PIXEL ** image = (PIXEL **)malloc(infoheader->biHeight * sizeof(PIXEL *));
         for(int i = 0 ; i < infoheader->biHeight;i++){
             image[i] = (PIXEL *)malloc(infoheader->biWidth * sizeof(PIXEL));
         }
         read_image(file,&image,infoheader->biHeight,infoheader->biWidth);
         int * permutation = createPermutationFunction(infoheader->biHeight*infoheader->biWidth*3,(unsigned int)0);
         char * res = create_string_from_image(image,infoheader->biHeight*infoheader->biWidth*3,permutation,infoheader->biHeight,infoheader->biWidth,length_of_secret*8);

        fprintf(w_file, "%s", res);
        fclose(w_file);
    }
    else if(strcmp(argv[1],"-stringToImage") == 0){
    FILEHEADER * fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * file = fopen(argv[2],"r");
    read_file_header(file,&fileheader);
    read_info_header(file,&infoheader);
    if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
     if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
    int height = infoheader->biHeight;
    int width =  infoheader->biWidth;
    FILE * file_text = fopen(argv[3],"r");
    char * text = file_read(file_text);
    PIXEL ** image = (PIXEL **)malloc(height*sizeof(PIXEL *));
    for(int i = 0 ; i < height;i++){
        image[i] = (PIXEL *)calloc(sizeof(PIXEL),width);
    }
    create_image_with_encoded_text(&image,text,height,width);
    char * new_file_name = (char *)malloc(strlen(argv[2]) + 5);
    strcpy(new_file_name,"new-");
    strcat(new_file_name,argv[2]);
    FILE * encrypted_image = fopen(new_file_name, "w+");
    write_file_header(encrypted_image,fileheader);
    write_info_header(encrypted_image,infoheader);
    write_image_to_decoded_file(encrypted_image,image,height,width);
    fclose(encrypted_image);
    }
    else if(strcmp(argv[1],"-imageToString") == 0){
    FILEHEADER * fileheader = (FILEHEADER *)malloc(sizeof(FILEHEADER));
    INFOHEADER * infoheader = (INFOHEADER *)malloc(sizeof(INFOHEADER));
    FILE * encrypted_image = fopen(argv[2],"r"); 
    read_file_header(encrypted_image, &fileheader);
    read_info_header(encrypted_image, &infoheader);
    if(fileheader->bfType1 != 'B' || fileheader->bfType2 != 'M'){
            printf("THE FILE GIVEN IS NOT A .BMP FILE!\n");
            return 1;
        }
     if(infoheader->biCompression == 1){
                printf("THE FILE IS COMPRESSED PLEASE NEXT TIME GIVE A NOT COMPRESSED FILE!\n");
                return 1;
            }
            if(infoheader->biBitCount != 24){
                printf("THE FILE GIVEN IS NOT A 24-BIT FILE!\n");
                return 1;
            }
    int height = infoheader->biHeight;
    int width = infoheader->biWidth;
    PIXEL ** image = (PIXEL **)malloc(height*sizeof(PIXEL *));
    for(int i = 0 ; i < height ; i++){
        image[i] = (PIXEL *)malloc(width*sizeof(PIXEL));
    }
    read_image(encrypted_image,&image,height,width);
    FILE * w_file = fopen("outputText.txt","w");
    char * decrypted_text = decrypt_text_from_image(image,height,width,w_file);
    }

    return 0;
}
