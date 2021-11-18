#include "../header.h"

#include <stdio.h>

void Insert(REGISTER registerData)
{
    /*
    abre DataResult.bin
    recebe o registro a ser inserido
    salva o tamanho dele - size (vamos usar para comparar daqui a pouco)
    endereco = verifica(endereco que ta no header, size);
        se endereco for -1
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