#ifndef HEADER_H
#define HEADER_H

typedef struct s_Key {
    int ClientId;
    int MovieId;
} KEY;

typedef struct s_Register {
    
    int ClientId;
    int MovieId;
    char ClientName[50];
    char MovieName[50];
    char Genre[50];
} REGISTER;

void Insert(REGISTER registerData);
void Remove(KEY key);
void Compress();
int Verifica(int address, int size);

#endif 
