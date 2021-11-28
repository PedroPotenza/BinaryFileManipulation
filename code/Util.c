#include "../header.h"

#include <stdio.h>

int Verifica(int address, int size)
{
    /*
    verifica quanto espaço tem aquele endereco de memoria 
        se ele for -1 
            retorna -1
        se ele for maior q size 
            retorna esse endereco 
        senao
            result = verifica (o proximo)
    return result
    */
}

//Roubei funcoes prontas que usei nos exercicios da aula 3: 
//pra gerar essa documentacao daora to usando o vscode com a extensao "Doxygen Documentation Generator" (pra fazer só escrever /** >:D) 

/**
 * @brief Read the first byte of a register to know the size in bytes of that register (that moves the position indicator 1 byte forward)
 * 
 * @param file File to read
 * @return int Size of register in int
 */
int registerSize(FILE* file)
{
    char size;

    fread(&size, sizeof(char), 1, file);

    return (int)size;
  
}

/**
 * @brief Breaks a string using a char "#" to separate the fields of Info, in the same time, prints the field on console.
 * 
 * @param string string to be broken.
 */
void fields(char* string)
{

    // char* field;

    // field = strtok(string,"#");
    // printf("Client Id: %s\n", field);

    // field = strtok(NULL,"#");
    // printf("Movie Id: %s\n", field);

    // field = strtok(NULL,"#");
    // printf("Client Name: %s\n", field);

    // field = strtok(NULL,"#");
    // printf("Movie Name: %s\n", field);

    // field = strtok(NULL,"#");
    // printf("Genre: %s\n\n", field);

}