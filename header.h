#ifndef HEADER_H
#define HEADER_H

typedef struct s_Register {
    int IdCliente;
    int IdFilme;
    char NomeCliente[50];
    char NomeFilme[50];
    char Genero[50];
} REGISTER;

typedef struct s_Key {
    int IdCliente;
    int IdFilme;
} KEY;

void Insert(REGISTER registerData);
void Remove(KEY key);
void Compress();
int Verifica(int address, int size);

#endif // MACRO
