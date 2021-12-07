#include "../header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int findAdressToFit(int adressToSee, int registerSize, FILE* file){

    if(adressToSee == -1)
        return -1;

    fseek(file, adressToSee, SEEK_SET);
    int localSize;
    fread(&localSize, sizeof(int), 1, file);

    if(localSize >= registerSize){
        return adressToSee;
    } else {
        fseek(file, 1 * sizeof(char), SEEK_CUR);
        int newAdressToSee;
        fread(&newAdressToSee, sizeof(int), 1, file);
        return findAdressToFit(newAdressToSee, registerSize, file);
    }

}

int Insert(REGISTER registerData)
{
    if(registerData.Id.ClientId == 0 || registerData.Id.MovieId == 0) {
        printf("Registro nulo não inserido\n");
        return 0;
    }

    char realMarker = '$';
    char removedMarker = '*';
    char divider = '#';

    
    FILE* resultFile;
    
    if( access("dataResult.bin", F_OK ) == 0 ) {
	    resultFile = fopen("dataResult.bin", "r+b");
	} else {
	    resultFile = fopen("dataResult.bin", "w+b");
	}

    //int registerSize = sizeof(registerData) + 6 * sizeof(char); //+ char pq falta contar a marca
    int registerSize = 2 * sizeof(int) + strlen(registerData.ClientName) + strlen(registerData.MovieName) + strlen(registerData.Genre) + 4 * sizeof(char);
    printf("tamanho do registro: %d\n", registerSize);
    // printf("tamanho do nome do Cliente: %d", );
    // printf("tamanho do nome do Filme: %d", );
    // printf("tamanho do nome do Genero: %d", );

    int offset;

    fread(&offset, sizeof(int), 1, resultFile);

    int registerAdress = findAdressToFit(offset, registerSize, resultFile);
    if (registerAdress == -1)
        fseek(resultFile, 0, SEEK_END);
    else {
        fseek(resultFile, registerAdress + sizeof(int) + 1 * sizeof(char), SEEK_SET);
        int newOffset;
        fread(&newOffset, sizeof(int), 1, resultFile);
        rewind(resultFile);
        fwrite(&newOffset, 1, sizeof(int), resultFile);
        fseek(resultFile, registerAdress, SEEK_SET);
    }

    fwrite(&registerSize, 1, sizeof(int), resultFile);
    fwrite(&realMarker, 1, sizeof(char), resultFile);
    fwrite(&registerData.Id.ClientId, 1, sizeof(int), resultFile);
    fwrite(&divider, 1, sizeof(divider), resultFile);
    fwrite(&registerData.Id.MovieId, 1, sizeof(int), resultFile);
    fwrite(&divider, 1, sizeof(divider), resultFile);
    fwrite(&registerData.ClientName, 1, strlen(registerData.ClientName), resultFile);
    fwrite(&divider, 1, sizeof(divider), resultFile);
    fwrite(&registerData.MovieName, 1, strlen(registerData.MovieName), resultFile);
    fwrite(&divider, 1, sizeof(divider), resultFile);
    fwrite(&registerData.Genre, 1, strlen(registerData.Genre), resultFile);

    if(registerAdress != -1)
        printf("Registro adicionado no byte %d do arquivo!", registerAdress);
    else
        printf("Registro adicionado no final do arquivo!");

    fclose(resultFile);
    return 1;
}
