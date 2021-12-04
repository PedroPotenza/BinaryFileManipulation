#include "../header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1;
#define false 0;

int ReadField(char* string, FILE* fileRead){

    char unit;
    int i = 0;

    while(fread(&unit, sizeof(char), 1, fileRead)){
        
        if(unit == '#')
            return i;

        string[i] = unit;
        i++;    
    }
    return i;
}

void MoveToNextField(FILE* fileRead){

    char unit;
    printf("\n----\n");

    while(fread(&unit, sizeof(char), 1, fileRead)){
        printf("%c", unit);
        if(unit == '|')
            fseek(fileRead, -sizeof(int), SEEK_CUR);
            fseek(fileRead, -sizeof(char), SEEK_CUR);
            break;
    }

    printf("\n----\n");
}

void Compress()
{
    FILE* fileRead;
    FILE* fileWrite;

    char realMarker = '$';
    char removedMarker = '*';
    char initializer = '|';
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

    fseek(fileRead, sizeof(int), SEEK_SET);
    
    int offset = 0;
    fwrite(&offset, 1, sizeof(int), fileWrite);

    int data;
    fread(&data, sizeof(int), 1, fileRead);
    fwrite(&data, 1, sizeof(int), fileWrite);
    fread(&data, sizeof(int), 1, fileRead);
    fwrite(&data, 1, sizeof(int), fileWrite);

    int size;
    char mark;
    char field[50];
    int fieldSize;
    int g = 0;

    while(fread(&size, sizeof(int), 1, fileRead)){
        printf("\niteracao %d\n", g);

        fseek(fileRead, sizeof(char), SEEK_CUR);
        fread(&mark, sizeof(char), 1, fileRead);

        printf("\nMark: %c -> Real %c\n", mark, realMarker);
        printf("FTELL = %ld", ftell(fileRead));

        if(mark == realMarker){
            fwrite(&size, 1, sizeof(int), fileWrite);
            fwrite(&initializer, 1, sizeof(divider), fileWrite);
            fwrite(&mark, 1, sizeof(char), fileWrite);

            int key;

            fread(&key, sizeof(int), 1, fileRead);
            fwrite(&key, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fseek(fileRead, sizeof(char), SEEK_CUR); //cuidado com o divider do fileRead
            fread(&key, sizeof(int), 1, fileRead);
            fwrite(&key, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fseek(fileRead, sizeof(char), SEEK_CUR); //cuidado com o divider do fileRead

            fieldSize = ReadField(field, fileRead);

            fwrite(&field, 1, fieldSize, fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fieldSize = ReadField(field, fileRead);

            fwrite(&field, 1, fieldSize, fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fieldSize = ReadField(field, fileRead);

            fwrite(&field, 1, fieldSize, fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            MoveToNextField(fileRead);
            printf("\nRegistro adicionado no arquivo temporario!\n");

        } else {
            fseek(fileRead, size-2, SEEK_CUR);
            printf("\nRegistro excluido do temporario!\n");
            MoveToNextField(fileRead);
        }
        g++;
    };
    

    fclose(fileRead);
    fclose(fileWrite);
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