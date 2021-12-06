#include "../header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

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

    fseek(fileRead, sizeof(int), SEEK_SET); //pula o offset antigo
    
    int offset = -1;
    fwrite(&offset, 1, sizeof(int), fileWrite); //escreve um offset zerado

    int data;
    fread(&data, sizeof(int), 1, fileRead); //preenche os dados dos vetores 
    fwrite(&data, 1, sizeof(int), fileWrite);
    fread(&data, sizeof(int), 1, fileRead);
    fwrite(&data, 1, sizeof(int), fileWrite);

    int size;

    char stringRegister[sizeof(REGISTER) + 6];
    char mark;
	
    while(fread(&size, sizeof(int), 1, fileRead)){ //le o tamanho
        
        fread(&mark, sizeof(char), 1, fileRead);

        //printf("\n%s", stringRegister);

        if(mark == realMarker){

            fwrite(&size, 1, sizeof(int), fileWrite);
            fwrite(&realMarker, 1, sizeof(char), fileWrite);

            int key;
            fread(&key, sizeof(int), 1, fileRead);
            fwrite(&key, 1, sizeof(int), fileWrite);

            fseek(fileRead,sizeof(char), SEEK_CUR);
            fwrite(&divider, 1, sizeof(char), fileWrite);

            fread(&key, sizeof(int), 1, fileRead);
            fwrite(&key, 1, sizeof(int), fileWrite);

            fseek(fileRead,sizeof(char), SEEK_CUR);
            fwrite(&divider, 1, sizeof(char), fileWrite);

            fread(stringRegister, size - (2*sizeof(int) + 2*sizeof(char)), sizeof(char), fileRead); //ele vai olhar so as strings.
            fwrite(stringRegister, size - (2*sizeof(int) + 2*sizeof(char)), sizeof(char), fileWrite);

            //fazer ele andar ate a marcacao do proximo registro e retornar 1 char e 1 int pra ele ir para a proxima iteracao de fato caso tenha lixo do registro anterior

            printf("Registro adicionado no arquivo temporario!\n");

        } else {
            fseek(fileRead, size, SEEK_CUR);
            printf("Registro excluido do temporario!\n");
        }

       /*fseek(fileRead, sizeof(char), SEEK_CUR); // le o pipe
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

            int seeIfHaveAnotherRegister;

            if(!fread(&seeIfHaveAnotherRegister, sizeof(int), 1, fileRead)){
                break;
            }
            fseek(fileRead, -sizeof(char), SEEK_CUR);

            MoveToNextField(fileRead); // le o lixo 
            printf("\nRegistro adicionado no arquivo temporario!\n");

        } else {
            fseek(fileRead, size-2, SEEK_CUR);
            printf("\nRegistro excluido do temporario!\n");
            MoveToNextField(fileRead);
        }*/
        // g++;
    };
    
    fclose(fileRead);
    fclose(fileWrite);

    if (remove("dataResult.bin") == 0) {
        printf("\ndataResult.bin deletado!");
    } else {
        printf("\n Nao foi possivel deletar dataResult.bin!");
    }

    int result = rename("Temp.bin", "dataResult.bin");
    if (result == 0) {
        printf("\nTemp.bin renomeado com sucesso para dataResult.bin!\n");
    } else {
        printf("\nNão foi possivel renomear Temp.bin para dataResult.bin!\n");
    }
    
}
