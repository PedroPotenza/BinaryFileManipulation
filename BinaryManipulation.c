#include <stdio.h>
#include <stdlib.h>

#include "code/Insert.c"
#include "code/Remove.c"
#include "code/Compress.c"
#include "code/Util.c"

#define true 1;
#define false 0;

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


int main(int argc, char const *argv[])
{
    
    //le o arquivo insere.bin
    FILE* file;
    if ((file = fopen("insere.bin", "rb")) == NULL)
    {
        printf("The file cannot be open.");
        return 0;
    }

    REGISTER* insertData;
    int insertSize = 0;
    
    while(fread(insertData, sizeof(REGISTER), 1, file))
    {
        insertSize++;
        
    }

    rewind(file);

    insertData = (REGISTER *) malloc(insertSize * sizeof(REGISTER));

    for (int i = 0; i < insertSize; i++)
    {
        REGISTER registerLocal;
        fread(&registerLocal, sizeof(REGISTER), 1, file);

        insertData[i] = registerLocal;
    }
    

    for (int i = 0; i < insertSize; i++)
    {
        printf("%d", insertData[i].Id.ClientId);

    }
    

        
        
    //fecha insere.bin

    

    
    //le o arquivo remove.bin
        //preenche o vetor removeData[]
    //fecha remove.bin

    // KEY* removeData;

    //le o arquivo DataResult.bin
        //recebe as 2 infos do header sobre os vetores 
        //posicao_para_inserir = segundo campo do header
        //posicao_para_remover = terceiro campo do header

    int posicao_para_inserir = 0;
    int posicao_para_remover = 0;

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
            //Insert(/*insertData[posicao_para_inserir]*/);
            posicao_para_inserir++;
            break;

        case 2:
            //Remove(/*removeData[posicao_para_remover]*/);
            posicao_para_remover++;
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