#ifndef HEADER_H
#define HEADER_H

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

void Insert(REGISTER registerData);
int Remove(KEY key);
void Compress();
int Verifica(int address, int size);

#endif 
