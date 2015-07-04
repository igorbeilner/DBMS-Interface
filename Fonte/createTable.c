//cria tabela
#include "buffend.h"

void createTable(rc_insert *t) {
	int size;
    strcpylower(t->tableName, t->tableName);        //muda pra minúsculo
    char *tableName = t->tableName, fkTable[TAMANHO_NOME_TABELA], fkColumn[TAMANHO_NOME_CAMPO];


    strcat(tableName, ".dat");                  //tableName.dat

    if(existeArquivo(tableName)){
        printf("TABELA JÁ EXISTE!!\n");
        return;
    }

    table *tab = iniciaTabela(t->tableName);    //cria a tabela

    int i;
    for(i=0; i < t->N; i++){
    	printf("%c\n", t->type[i]);
    	if (t->type[i] == 'S') {
    		size = atoi(t->values[i]);
    	} else {
    		size = 0;
    	}

    	if (t->attribute[i] == FK) {
    		strncpylower(fkTable, t->fkTable[i], TAMANHO_NOME_TABELA);
    		strncpylower(fkColumn,t->fkColumn[i], TAMANHO_NOME_CAMPO);
    	} else {
    		fkTable[0] = '\0';
    		fkColumn[0] = '\0';
    	}
        tab = adicionaCampo(tab, t->columnName[i], t->type[i], size, (int)t->attribute[i], fkTable, fkColumn);
    }
    finalizaTabela(tab);
}
