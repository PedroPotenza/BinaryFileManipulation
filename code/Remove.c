#include "../header.h"

#include <stdio.h>

void Remove(KEY key)
{
    /*
    recebe a chave a ser removida “CodCli+CodF”
    abre DataResult.bin
    removido = false
    percorre todos os registros
        se a chave bate
            printa o registro a ser removido (acho bom q assim a gente sempre vai ter nocao das coisas)
            printa falando que a remocao foi feita com sucesso
            marca o segundo campo com * 
            marca o endereco que tinha no header
            muda o endereco do header para o endereco desse registro
            removido = true
    se removido = false
        printa falando que nao foi possivel localizar chave
    fecha DataResult.bin
    */

}