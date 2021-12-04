#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code/Insert.c"
#include "code/Remove.c"
#include "code/Compress.c"
#include "code/Util.c"

#define true 1
#define false 0

/*

    SORBE O ARQUIVO QUE TEREMOS COMO RESULTADO (DataResult.bin):
    header vai ter 3 informacoes: 
        - 1 int q vai ser o endereco de memoria da lista de removidos
        - 1 char para salvar que posicao do vetor de inserir paramos (aqui pode ser char pq n vai passar de 255)
        - 1 char para salvar que posicao do vetor de remocao paramos (aqui pode ser char pq n vai passar de 255)

    SOBRE O REGISTRO:
    primeiro campo: Tamanho do Registro
    segundo campo: Valido ($) ou Invalido (*)
    terceiro campo: Codigo do Cliente
    quarto campo: Codigo do Filme
    quinto campo: Nome do Cliente
    sexto campo: Nome do Filme
    setimo campo: Genero

    A partir do terceiro campo, eles vao ser separados usando # (obrigatorio) 
    EXEMPLO: 61$1#1#João da Silva# Indiana Jones e a Última Cruzada#Aventura
*/

FILE * file_open_read(char * filename) {
	FILE *file = fopen(filename, "rb");
	
	if(file == NULL) {
		printf("The file %s cannot be open.", filename);
		exit(1);
	}
	
	return file;	
}

FILE * connect_DB() {
	char * filename = "dataResult.bin";
	
	if(access(filename, F_OK ) == 0)
		return fopen(filename, "r+b");
		
	FILE * file = fopen(filename, "w+b");
	
	int ZERO = 0;
	int LISTA_VAZIA = -1;
	fwrite(&LISTA_VAZIA, sizeof(int), 1, file);
	fwrite(&ZERO, sizeof(int), 1, file);
	fwrite(&ZERO, sizeof(int), 1, file);
	
	return file;
}


int main(int argc, char const *argv[])
{
    //le o arquivo insere.bin
    FILE* file = file_open_read("insere.bin");

    REGISTER* insertData;
    int insertSize = 4;

    insertData = (REGISTER*) malloc(insertSize * sizeof(REGISTER));

    fread(insertData, sizeof(REGISTER), insertSize, file);
    fclose(file);
    
    file = file_open_read("remove.bin");

    KEY* removeData;
    int removeSize = 3;
    
    removeData = (KEY*) malloc(removeSize * sizeof(KEY));
    
    fread(removeData, sizeof(KEY), removeSize, file);
    fclose(file);
    
    file = connect_DB();
    
    int inseridos = 0;
    int removidos = 0;

    fseek(file, sizeof(int), SEEK_SET);
    fread(&inseridos, sizeof(int), 1, file);
    fread(&removidos, sizeof(int), 1, file);

    printf("Inseridos: %d\n", inseridos);
    printf("Removidos: %d\n", removidos);

    fclose(file);

    printf("--------- MENU ---------\n");
    printf(" (1) - Inserir Registro\n");
    printf(" (2) - Remover Registro\n");
    printf(" (3) - Compactar Arquivo\n");
    printf(" (4) - Sair\n");
    
    int option, repeat = true;
    while(repeat)
    {

        printf("Opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            Insert(insertData[inseridos]);
            inseridos++;
            printf("\nInseridos para escrever: %d\n", inseridos);
            
            if ((file = fopen("dataResult.bin", "r+b")) == NULL)
            {
                printf("The result file cannot be open.");
                return 0;
            }
            rewind(file);
            fseek(file, 4, SEEK_SET);
            fwrite(&inseridos, 1, sizeof(int), file);
            fclose(file);
            break;

        case 2:
            if (Remove(removeData[removidos]) == 1) {
                removidos++;
                printf("\nRemovidos para escrever: %d\n", removidos);
                
                if ((file = fopen("dataResult.bin", "r+b")) == NULL)
                {
                    printf("The result file cannot be open.");
                    return 0;
                }
                rewind(file);
                fseek(file, 8, SEEK_SET);
                fwrite(&removidos, 1, sizeof(int), file);
                fclose(file);
            }
            break;

        case 3:
            Compress();
            break;

        case 4:
            printf("Finalizando...\n\n\n");
            repeat = false;
            break;
        
        default:
            break;
        }
    }

    return 0;
}
