#include<stdio.h>

int main() {
    FILE *fd;
    
    //////////////////////////////
    struct CliF {
        int CodCli;
        int CodF;
        char NomeCli[50];
        char NomeF[50];
        char Genero[50];
    } vet[8] = {{1, 1, "Cli-1", "Filme-1-1", "Gen-1"},              
                {1, 2, "Cli-1", "Filme-1-2", "Gen-1"},
				{1, 3, "Cli-1", "Filme-1-3", "Gen-1"},
				
				{2, 1, "Cli-2", "Filme-2-1", "Gen-2"},              
                {2, 2, "Cli-2", "F-2-2", "Gen-2"},
				{2, 3, "Cli-2", "Filme-2-3", "Genero-2"},
				
				{3, 1, "Cli-3", "Filme-3-1", "Gen-3"},              
                {3, 2, "Cli-3", "Filme-3-2", "Gen-3"}
				};
       
    fd = fopen("insere.bin", "w+b");
    fwrite(vet, sizeof(vet), 1, fd);
    fclose(fd);
    
    //////////////////////////////
	struct remove {
        int CodCli;
        int CodF;
    } vet_r[4] = {{1,3},
                  {2,1},
                  {1,1},
                  {3,2}};
       
    fd = fopen("remove.bin", "w+b");
    fwrite(vet_r, sizeof(vet_r), 1, fd);
    fclose(fd);
}

