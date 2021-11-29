#include "../header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1;
#define false 0;

void Compress()
{
    FILE* fileRead;
    FILE* fileWrite;

    char realMarker = '$';
    char removedMarker = '*';
    char divider = '#';

    if ((fileRead = fopen("dataResult.bin", "rb")) == NULL)
    {
        printf("The result file cannot be open.");
        return;
    }

    if ((fileWrite = fopen("Temp.bin", "wb")) == NULL)
    {
        printf("The result file cannot be open.");
        return;
    }

    int data[3];

    fread(data, sizeof(int), 3, fileRead);
    fwrite(&data, 3, sizeof(int), fileWrite);

    int size;
    char mark;

    while(fread(&size, sizeof(int), 1, fileRead)){
        
        if(size == 0)
            break;

        fread(&mark, sizeof(char), 1, fileRead);
        
        if(mark == realMarker){
            fwrite(&size, 1, sizeof(int), fileWrite);
            fwrite(&mark, 1, sizeof(char), fileWrite);

            REGISTER registerData;

            fread(&registerData.Id.ClientId, sizeof(int), 1, fileRead);
            fwrite(&registerData.Id.ClientId, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fread(&registerData.Id.MovieId, sizeof(int), 1, fileRead);
            fwrite(&registerData.Id.MovieId, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fread(&registerData.ClientName, sizeof(int), 1, fileRead);
            fwrite(&registerData.ClientName, 1, strlen(registerData.ClientName), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fread(&registerData.MovieName, sizeof(int), 1, fileRead);
            fwrite(&registerData.MovieName, 1, strlen(registerData.MovieName), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fread(&registerData.Genre, sizeof(int), 1, fileRead);
            fwrite(&registerData.Genre, 1, strlen(registerData.Genre), fileWrite);

            printf("\nRegistro adicionado no arquivo temporario!\n");

        } else {

            fseek(fileRead, size-1, SEEK_CUR);
            printf("\nRegistro excluido do temporario!\n");

        }

        fclose(fileRead);
        fclose(fileWrite);
    };
    
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