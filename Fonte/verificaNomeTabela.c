//BufferPool
#include "buffend.h"

int verificaNomeTabela(char *nomeTabela) {

    FILE *dicionario;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    char *nomeAux = (char *)malloc(sizeof(char)*(strlen(nomeTabela)+1));

    if((dicionario = fopen("fs_object.dat","a+b")) == NULL){
		free(tupla);
        return ERRO_ABRIR_ARQUIVO;
    }

    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, dicionario); //Lê somente o nome da tabela

        strcpy(nomeAux, nomeTabela);
        nomeAux[strlen(nomeTabela)] = '\0';

        if(strcmp(toUppercase(tupla), toUppercase(nomeAux)) == 0){ // Verifica se o nome dado pelo usuario existe no dicionario de dados.
            free(tupla);
            free(nomeAux);
            return 1;
        }

        fseek(dicionario, 28, 1);
    }

    fclose(dicionario);
    free(tupla);
    free(nomeAux);

    return 0;
}