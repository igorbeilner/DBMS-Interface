//cria tabela
#include "buffend.h"


int verifyFK(table *tab, char *tableName, int attr){
    if(verificaNomeTabela(tableName)){
        struct fs_objects objeto = leObjeto(tableName);
        tp_table *esquema = leSchema(objeto);
		if(esquema == ERRO_ABRIR_ESQUEMA){
            printf("error: Não foi possível criar o esquema.\n");
            return 0;
        }

        for(; esquema != NULL; esquema = esquema->next){
            if(objcmp(esquema->nome, tableName) == 0){
                if(esquema->chave == PK){
                    return 1;
                }
            }
        }
    }
	return 0;
}

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
        if(verifyFK(tab, t->objName, t->attribute[i]) == 0){
			printf("ERROR: attribute FK cannot be references");
			return;
		}
    }

    printf("%s\n",(finalizaTabela(tab) == SUCCESS)? "CREATE TABLE": "ERROR:   Table already exists!\n");
}
