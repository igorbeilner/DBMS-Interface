//BufferPool
#include "buffend.h"

int verificaNomeTabela(char *nomeTabela) {

    FILE *dicionario;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    if((dicionario = fopen("fs_object.dat","a+b")) == NULL){
		free(tupla);
        return ERRO_ABRIR_ARQUIVO;
    }

    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, dicionario); //Lê somente o nome da tabela

        if(strcmp(tupla, nomeTabela) == 0){ // Verifica se o nome dado pelo usuario existe no dicionario de dados.
            free(tupla);
            return 1;
        }
        
        fseek(dicionario, 28, 1);
    }

    fclose(dicionario);
    free(tupla);

    return 0;
}