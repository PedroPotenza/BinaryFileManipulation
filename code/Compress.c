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

    while(fread(&unit, sizeof(char), 1, fileRead)){ //le byte por byte até achar o pipe
        printf("%c", unit);
        if(unit == '|') 
            break;
    }

    fseek(fileRead, -sizeof(int), SEEK_CUR);  //como o pipe ta depois do size, devemos voltar sua posição
    fseek(fileRead, -sizeof(char), SEEK_CUR); //como o pipe foi lido, devemos voltar sua posição

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

    fseek(fileRead, sizeof(int), SEEK_SET); //pula o offset antigo
    
    int offset = 0;
    fwrite(&offset, 1, sizeof(int), fileWrite); //escreve um offset zerado

    int data;
    fread(&data, sizeof(int), 1, fileRead); //preenche os dados dos vetores 
    fwrite(&data, 1, sizeof(int), fileWrite);
    fread(&data, sizeof(int), 1, fileRead);
    fwrite(&data, 1, sizeof(int), fileWrite);

    int size;
    char mark;
    char field[50];
    int fieldSize;
    int g = 0;

    while(fread(&size, sizeof(int), 1, fileRead)){ //le o tamanho
        printf("\niteracao %d\n", g);

        fseek(fileRead, sizeof(char), SEEK_CUR); // le o pipe
        fread(&mark, sizeof(char), 1, fileRead); // le a marca

        printf("\nMark: %c -> Real %c\n", mark, realMarker);
        printf("FTELL = %ld", ftell(fileRead));

        if(mark == realMarker){ //se o registro é valido

            fwrite(&size, 1, sizeof(int), fileWrite);
            fwrite(&initializer, 1, sizeof(char), fileWrite);
            fwrite(&mark, 1, sizeof(char), fileWrite);

            int key;

            fread(&key, sizeof(int), 1, fileRead); //le a chave do cliente
            fwrite(&key, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fseek(fileRead, sizeof(char), SEEK_CUR); // pula o divider
            fread(&key, sizeof(int), 1, fileRead); // le a chave do filme
            fwrite(&key, 1, sizeof(int), fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fseek(fileRead, sizeof(char), SEEK_CUR); // pula o divider

            fieldSize = ReadField(field, fileRead); //le o nome do cara ate o #

            fwrite(&field, 1, fieldSize, fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fieldSize = ReadField(field, fileRead); //le o nome do filme ate o #

            fwrite(&field, 1, fieldSize, fileWrite); 
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            fieldSize = ReadField(field, fileRead); //le o nome do genero ate o #

            fwrite(&field, 1, fieldSize, fileWrite);
            fwrite(&divider, 1, sizeof(divider), fileWrite);

            MoveToNextField(fileRead); // le o lixo 
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