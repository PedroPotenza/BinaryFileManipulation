#include "../header.h"

#include <stdio.h>

void Insert(REGISTER registerData)
{
    char realMarker[] = "$";
    char removedMarker[] = "*";
    char divider[] = "#";

    // char clientName[] = registerData.ClientName;
    // char movieName[] = registerData.MovieName;
    // char genre[] = registerData.Genre;
    
    FILE* file;

    if ((file = fopen("dataResult.bin", "rb")) == NULL)
    {
        printf("The result file cannot be open.");
        return;
    }

    int registerSize = sizeof(registerData);
    
    int offset = 0;
    int inseridos = 0;

    fread(&offset, sizeof(int), 1, file);
    fread(&inseridos, sizeof(int), 1, file);
    fseek(file, sizeof(int), SEEK_CUR);

    printf("Offset: %d", offset);
    if (offset == 0) {
        fseek(file, 0, SEEK_END);
        fwrite(&registerSize, 1, sizeof(int), file);
        fwrite(realMarker, 1, sizeof(realMarker), file);
        fwrite(&registerData.Id.ClientId, 1, sizeof(int), file);
        fwrite(divider, 1, sizeof(divider), file);
        fwrite(&registerData.Id.MovieId, 1, sizeof(int), file);
        fwrite(divider, 1, sizeof(divider), file);
        fwrite(&registerData.ClientName, 1, sizeof(registerData.ClientName), file);
        fwrite(divider, 1, sizeof(divider), file);
        fwrite(&registerData.MovieName, 1, sizeof(registerData.MovieName), file);
        fwrite(divider, 1, sizeof(divider), file);
        fwrite(&registerData.Genre, 1, sizeof(registerData.Genre), file);
        fwrite(divider, 1, sizeof(divider), file);

        printf("Registro adicionado no final do arquivo!");
    }

    fclose(file);
    /*
    abre DataResult.bin
    recebe o registro a ser inserido
    salva o tamanho dele - size (vamos usar para comparar daqui a pouco)
    endereco = verifica(endereco que ta no header, size);
        se endereco for 0
            adiciona no final do arquivo DataResult.bin
            printa falando que o registro foi inserido com sucesso no final do arquivo
            return
        senao 
            adiciona no endereco
            printa falando que o registro foi inserido com sucesso a partir do byte "x"
    fecha DataResult.bin
    return
    */
}