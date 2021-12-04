#include "../header.h"

#include <stdio.h>
#include <string.h>

int findAdressToFit(int adressToSee, int registerSize, FILE* file){

    if(adressToSee == 0)
        return 0;

    fseek(file, adressToSee, SEEK_SET);
    int localSize;
    fread(&localSize, sizeof(int), 1, file);

    if(localSize >= registerSize){
        return adressToSee;
    } else {
        fseek(file, 2 * sizeof(char), SEEK_CUR);
        int newAdressToSee;
        fread(&newAdressToSee, sizeof(int), 1, file);
        return findAdressToFit(newAdressToSee, registerSize, file);
    }

}

void Insert(REGISTER registerData)
{
    char realMarker = '$';
    char removedMarker = '*';
    char initializer = '|';
    char divider = '#';

    
    FILE* resultFile;

    if ((resultFile = fopen("dataResult.bin", "r+b")) == NULL)
    {
        printf("The result file cannot be open.");
        return;
    }

    int registerSize = sizeof(registerData) + 8 * sizeof(char); //+ char pq falta contar a marca

    int offset = 0;

    fread(&offset, sizeof(int), 1, resultFile);

    int registerAdress = findAdressToFit(offset, registerSize, resultFile);
    if (registerAdress == 0)
        fseek(resultFile, 0, SEEK_END);
    else {
        fseek(resultFile, registerAdress + sizeof(int) + 2 * sizeof(char), SEEK_SET);
        int newOffset;
        fread(&newOffset, sizeof(int), 1, resultFile);
        rewind(resultFile);
        fwrite(&newOffset, 1, sizeof(int), resultFile);
        fseek(resultFile, registerAdress, SEEK_SET);
    }

    fwrite(&registerSize, 1, sizeof(int), resultFile);
    fwrite(&initializer, 1, sizeof(initializer), resultFile);
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
    fwrite(&divider, 1, sizeof(divider), resultFile);

    if(registerAdress != 0)
        printf("Registro adicionado no byte %d do arquivo!", registerAdress);
    else
        printf("Registro adicionado no final do arquivo!");

    fclose(resultFile);
}
