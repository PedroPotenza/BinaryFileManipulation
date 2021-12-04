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
        
        if(size == 0){
            exist = 0;
            break;
        }

        char mark;
        fseek(resultFile, sizeof(char), SEEK_CUR);
        fread(&mark, sizeof(char), 1, resultFile);

        if(mark == '*'){
            fseek(resultFile, size - 2, SEEK_CUR);
            continue;
        }

        fread(&readKey.ClientId, sizeof(int), 1, resultFile);
        fseek(resultFile, 1, SEEK_CUR);
        fread(&readKey.MovieId, sizeof(int), 1, resultFile);

        if(readKey.ClientId == key.ClientId || readKey.MovieId == key.MovieId) {

            printf("Registro Removido com sucesso!\n");

            fseek(resultFile, -(2 * sizeof(int) + 2), SEEK_CUR);
            char removedMark = '*';
            fwrite(&removedMark, 1, sizeof(char), resultFile);
            fwrite(&offset, 1, sizeof(int), resultFile);
            
            fseek(resultFile, -10, SEEK_CUR);
            int adress = ftell(resultFile);

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