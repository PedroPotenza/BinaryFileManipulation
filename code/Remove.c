#include "../header.h"

#include <stdio.h>

int Remove(KEY key)
{
    /*
    recebe a chave a ser removida “CodCli+CodF”
    abre DataResult.bin
    removido = false
    percorre todos os registros
        se a chave bate
            printa o registro a ser removido (acho bom q assim a gente sempre vai ter nocao das coisas)
            printa falando que a remocao foi feita com sucesso
            marca o segundo campo com * 
            marca o endereco que tinha no header
            muda o endereco do header para o endereco desse registro
            removido = true
    se removido = false
        printa falando que nao foi possivel localizar chave
    fecha DataResult.bin
    */

   FILE* resultFile;

    if ((resultFile = fopen("dataResult.bin", "r+b")) == NULL)
    {
        printf("The result file cannot be open.");
        return 0;
    }
    //Cabeçalho
    int offset;
    fread(&offset, sizeof(int), 1, resultFile);

    fseek(resultFile, 2 * sizeof(int), SEEK_CUR);

    int exist = 1;

    KEY readKey;

    int size;

    while(fread(&size, sizeof(int), 1, resultFile)){

        // printf("Size do registro: %d\n", size);
        
        if(size == 0){
            exist = 0;
            break;
        }

        char mark;
        fread(&mark, sizeof(char), 1, resultFile);
        // printf("Mark do registro: %c\n", mark);

        if(mark == '*'){
            fseek(resultFile, size, SEEK_CUR);
            // printf("Local apos o registro removido: %d\n", ftell(resultFile));
            continue;
        }

        fread(&readKey.ClientId, sizeof(int), 1, resultFile);
        fseek(resultFile, 1, SEEK_CUR); //divider
        fread(&readKey.MovieId, sizeof(int), 1, resultFile);

        // printf("==== comparacao importante ====\n");
        // printf("Chave do cliente do registro: %d \n", readKey.ClientId);
        // printf("Chave do cliente do remove.bin: %d \n", key.ClientId);
        // printf("Chave do filme do registro: %d \n", readKey.MovieId);
        // printf("Chave do cliente do remove.bin: %d \n", key.MovieId);

        if(readKey.ClientId == key.ClientId || readKey.MovieId == key.MovieId) {

            printf("Registro Removido com sucesso!\n");

            fseek(resultFile, -(3 * sizeof(int) + 2), SEEK_CUR);
            int adress = ftell(resultFile);
            fseek(resultFile, sizeof(int), SEEK_CUR);
            char removedMark = '*';
            fwrite(&removedMark, 1, sizeof(char), resultFile);
            fwrite(&offset, 1, sizeof(int), resultFile);
            char trash = '-';
            for (int i = 0; i < size - sizeof(int); i++)
            {
                fwrite(&trash, 1, sizeof(char), resultFile);
            }
             
            rewind(resultFile);
            fwrite(&adress, 1, sizeof(int), resultFile);
            fclose(resultFile);

            exist = 0;
            return 1;
        }

    }
    
    printf("Nao foi possivel localizar tal chave!\n");
    return 0;
}