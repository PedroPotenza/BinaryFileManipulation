#include "../header.h"

#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;

void Compress()
{
    // FILE* fileRead;
    // FILE* fileWrite;

    // char realMarker = '$';
    // char removedMarker = '*';
    // char divider = '#';

    // if ((fileRead = fopen("dataResult.bin", "rb")) == NULL)
    // {
    //     printf("The result file cannot be open.");
    //     return;
    // }

    // if ((fileWrite = fopen("Temp.bin", "wb")) == NULL)
    // {
    //     printf("The result file cannot be open.");
    //     return;
    // }

    // int data[3];

    // fread(data, sizeof(int), 3, fileRead);
    // fwrite(&data, 3, sizeof(int), fileWrite);

    // int size;
    // char mark;
    // int end = true;

    // do{
        
    //     fread(size, sizeof(int), 1, fileRead);
    //     if(size == 0)
    //         end = false;
    //     fread(mark, sizeof(char), 1, fileRead);
        
    //     if(mark == realMarker){
    //         fwrite(&size, 1, sizeof(int), fileWrite);
    //         fwrite(&mark, 1, sizeof(char), fileWrite);

    //         int x[2];
    //         fread(x, sizeof(x), 1, fileRead);

    //         fwrite(&x[0], 1, sizeof(int ))

    //         char string[size];
    //         fread(&string, size, 1 , fileRead);
    //         fwrite(&)



    //     }



    // } while(end);
    


    // while(fread(size, sizeof(int), 1, fileRead))
    // {
    //     char mark;
    //     fread(mark, sizeof(char), 1, fileRead);

    //     if(mark != removedMarker){

    //     }
    // }






















    /*
    Abre DataResult.bin como leitura 
    Abre Temp.bin como criar + escrita
    do
        size = le o primeiro campo do registro
        valid = le o segundo campo do registro 
        se valid é $ (valido)
            escreve o registro no arquivo temporario
        se valid é * (invalido)
            pula esse registro usando o size 
    while(size != 0)
    deleta DataResult.bin
    renomeia o Temp.bin para DataResult.bin
    printa falando que o arquivo foi comprimido 
    */
}