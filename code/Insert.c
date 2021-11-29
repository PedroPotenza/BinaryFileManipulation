#include "../header.h"

#include <stdio.h>

int findAdressToFit(int adressToSee, int registerSize, FILE* file){

    int registerAdress = 0;

    if(adressToSee == 0)
        return 0;

    fseek(file, adressToSee, SEEK_SET);
    int localSize;
    fread(&localSize, sizeof(int), 1, file);

    if(localSize < registerSize){
        return adressToSee;
    } else {
        
        fseek(file, sizeof(char), SEEK_CUR);
        int newAdressToSee;
        fread(&newAdressToSee, sizeof(int), 1, file);
        return findAdressToFit(newAdressToSee, registerSize, file);

    }

}

void Insert(REGISTER registerData)
{
    char realMarker = '$';
    char removedMarker = '*';
    char divider = '#';
    
    FILE* file;

    if ((file = fopen("dataResult.bin", "wb")) == NULL)
    {
        printf("The result file cannot be open.");
        return;
    }

    int registerSize = sizeof(registerData) + 6*sizeof(char); //+ char pq falta contar a marca
    
    int offset = 0;

    fread(&offset, sizeof(int), 1, file);

    int registerAdress = findAdressToFit(offset, registerSize, file);
    if (registerAdress == 0)
        fseek(file, 0, SEEK_END);
    else 
        fseek(file, registerAdress, SEEK_SET);

    fwrite(&registerSize, 1, sizeof(int), file);
    fwrite(&realMarker, 1, sizeof(char), file);
    fwrite(&registerData.Id.ClientId, 1, sizeof(int), file);
    fwrite(&divider, 1, sizeof(divider), file);
    fwrite(&registerData.Id.MovieId, 1, sizeof(int), file);
    fwrite(&divider, 1, sizeof(divider), file);
    fwrite(&registerData.ClientName, 1, sizeof(registerData.ClientName), file);
    fwrite(&divider, 1, sizeof(divider), file);
    fwrite(&registerData.MovieName, 1, sizeof(registerData.MovieName), file);
    fwrite(&divider, 1, sizeof(divider), file);
    fwrite(&registerData.Genre, 1, sizeof(registerData.Genre), file);
    fwrite(&divider, 1, sizeof(divider), file);

    if(registerAdress != 0)
        printf("Registro adicionado no byte %d do arquivo!", registerAdress);
    else
        printf("Registro adicionado no final do arquivo!");

    fclose(file);
   
}

