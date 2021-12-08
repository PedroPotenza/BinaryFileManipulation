/*
    Sobre o dataResult.bin :
    Header contém 3 informacoes: 
        - 1 int q vai ser o endereco de memoria da lista de removidos
        - 1 char para salvar que posicao do vetor de inserir paramos (aqui pode ser char pq n vai passar de 255)
        - 1 char para salvar que posicao do vetor de remocao paramos (aqui pode ser char pq n vai passar de 255)

    Campos do registro :
        primeiro campo: Tamanho do Registro
        segundo campo: Valido ($) ou Invalido (*)
        terceiro campo: Codigo do Cliente
        quarto campo: Codigo do Filme
        quinto campo: Nome do Cliente
        sexto campo: Nome do Filme
        setimo campo: Genero

    A partir do terceiro campo, eles vao ser separados usando # (obrigatorio) 
        Exemplo: 61$1#1#João da Silva# Indiana Jones e a Última Cruzada#Aventura
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*-------------------------------------- Globals --------------------------------------*/
#define true 1
#define false 0

/*-------------------------------------- Structs --------------------------------------*/
typedef struct s_Key {
    int ClientId;
    int MovieId;
} KEY;

typedef struct s_Register {
    
    KEY Id;
    char ClientName[50];
    char MovieName[50];
    char Genre[50];
} REGISTER;

/*-------------------------------------- Header --------------------------------------*/
int Insert(REGISTER registerData);
int Remove(KEY key);
void Compress();
int Verifica(int address, int size);

/*-------------------------------------- Utils --------------------------------------*/
FILE * fileOpenRead(char * filename) {
	FILE *file = fopen(filename, "rb");
	
	if(file == NULL) {
		printf("The file %s cannot be open.", filename);
		exit(1);
	}
	
	return file;	
}

FILE * connectDB() {
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

/*-------------------------------------- Main --------------------------------------*/
int main(int argc, char const *argv[])
{
    FILE* file = fileOpenRead("insere.bin");

    REGISTER* insertData;
    int insertSize = 15;

    insertData = (REGISTER*) malloc(insertSize * sizeof(REGISTER));

    fread(insertData, sizeof(REGISTER), insertSize, file);
    fclose(file);
    
    file = fileOpenRead("remove.bin");

    KEY* removeData;
    int removeSize = 15;
    
    removeData = (KEY*) malloc(removeSize * sizeof(KEY));
    
    fread(removeData, sizeof(KEY), removeSize, file);
    fclose(file);
    
    file = connectDB();
    
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
    
    int option, repeat, inserted = true;
    while(repeat)
    {

        printf("Opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            inserted = Insert(insertData[inseridos]);
            if(inserted == true) {
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
            }
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

/*-------------------------------------- INSERE --------------------------------------*/
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

/*-------------------------------------- Remove --------------------------------------*/
int Remove(KEY key)
{

   FILE* resultFile;

    if ((resultFile = fopen("dataResult.bin", "r+b")) == NULL)
    {
        printf("The result file cannot be open.");
        return 0;
    }

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
        fread(&mark, sizeof(char), 1, resultFile);

        if(mark == '*'){
            fseek(resultFile, size, SEEK_CUR);
            continue;
        }

        fread(&readKey.ClientId, sizeof(int), 1, resultFile);
        fseek(resultFile, 1, SEEK_CUR); //divider
        fread(&readKey.MovieId, sizeof(int), 1, resultFile);

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

/*-------------------------------------- Compress --------------------------------------*/
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

    fseek(fileRead, sizeof(int), SEEK_SET);
    
    int offset = -1;
    fwrite(&offset, 1, sizeof(int), fileWrite);

    int data;
    fread(&data, sizeof(int), 1, fileRead); 
    fwrite(&data, 1, sizeof(int), fileWrite);
    fread(&data, sizeof(int), 1, fileRead);
    fwrite(&data, 1, sizeof(int), fileWrite);

    int size;

    char stringRegister[sizeof(REGISTER) + 6];
    char mark;
	
    while(fread(&size, sizeof(int), 1, fileRead)) {
        
        fread(&mark, sizeof(char), 1, fileRead);

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

            fread(stringRegister, size - (2*sizeof(int) + 2*sizeof(char)), sizeof(char), fileRead);
            fwrite(stringRegister, size - (2*sizeof(int) + 2*sizeof(char)), sizeof(char), fileWrite);

            char unit;
            do{
                fread(&unit, sizeof(char), 1, fileRead);
            }while(unit == '-');

            fseek(fileRead, -sizeof(char), SEEK_CUR);

            printf("Registro adicionado no arquivo temporario!\n");

        } else {
            fseek(fileRead, size, SEEK_CUR);
            printf("Registro excluido do temporario!\n");
        }
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