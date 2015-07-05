//cria tabela
#include "buffend.h"

void createTable(rc_insert *t) {
	int size;
    strcpylower(t->objName, t->objName);        //muda pra minúsculo
    char *tableName = (char*) malloc (TAMANHO_NOME_TABELA),
        fkTable[TAMANHO_NOME_TABELA], fkColumn[TAMANHO_NOME_CAMPO];

    strncpylower(tableName, t->objName, TAMANHO_NOME_TABELA);

    strcat(tableName, ".dat\0");                  //tableName.dat

    if(existeArquivo(tableName)){
        printf("ERROR:  Table already exists!\n");
        return;
    }

    table *tab = iniciaTabela(t->objName);    //cria a tabela

    int i;
    for(i=0; i < t->N; i++){
    	if (t->type[i] == 'S')
    		size = atoi(t->values[i]);
    	else if (t->type[i] == 'I')
    		size = sizeof(int);
    	else if (t->type[i] == 'D')
    		size = sizeof(double);

    	if (t->attribute[i] == FK) {
    		strncpylower(fkTable, t->fkTable[i], TAMANHO_NOME_TABELA);
    		strncpylower(fkColumn,t->fkColumn[i], TAMANHO_NOME_CAMPO);
    	} else {
    		strcpy(fkTable, "");
    		strcpy(fkColumn, "");
    	}

        tab = adicionaCampo(tab, t->columnName[i], t->type[i], size, t->attribute[i], fkTable, fkColumn);
        //tab = adicionaCampo(tab, "CPF"     , 'I', (sizeof(int))   ,PK,"","");
    }

    printf("%s\n",(finalizaTabela(tab) == SUCCESS)? "CREATE TABLE": "ERROR:   Table already exists!\n");
}
