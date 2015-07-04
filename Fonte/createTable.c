//cria tabela
#include "buffend.h"

void createTable(rc_insert *t){
    tolower(t->tableName, t->tableName);        //muda pra minúsculo
    char *tableName = t->tableName;

    strcat(tableName, ".dat");                  //tableName.dat

    if(existeArquivo(tableName)){
        printf("TABELA JÁ EXISTE!!\n");
        return;
    }

    table *tab = iniciaTabela(t->tableName);    //cria a tabela

    int i;
    for(i=0; i < t->N; i++){
        tab =
        adicionaCampo(tab, t->columnName[i], t->type[i], atoi(t->values[i]),
            (int)t->attribute[i], t->fkTable[i], t->fkColumn[i]);
    }
}
