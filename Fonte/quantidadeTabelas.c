//BufferPool
#include "buffend.h"

int quantidadeTabelas(){

    FILE *dicionario;
    int codTbl = 0;

    if((dicionario = fopen("fs_object.dat","a+b")) == NULL)
        return ERRO_ABRIR_ARQUIVO;

    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        codTbl++; // Conta quantas vezes é lido uma tupla no dicionario.

        fseek(dicionario, 48, 1);
    }

    fclose(dicionario);

    return codTbl;
}