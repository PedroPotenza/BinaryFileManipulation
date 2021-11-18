#include "../header.h"

#include <stdio.h>

void Compress()
{
    /*
    Abre DataResult.bin como leitura 
    Abre Temp.bin como criar + escrita
    do
        size = le o primeiro campo do registro
        valid = le o segundo campo do registro 
        se valid é $ (valido)
            escreve o registro no arquivo temporario
        se valid é * (invalido)
            pula esse registro usando o size 
    while(size != 0)
    deleta DataResult.bin
    renomeia o Temp.bin para DataResult.bin
    printa falando que o arquivo foi comprimido 
    */
}