#include "buffend.h"


int insere(rc_insert *nomeTabela) {

	int i;
	table *tabela = (table *)malloc(sizeof(tabela));
	column *colunas = NULL;
	struct fs_objects objeto;

	abreTabela(nomeTabela->tableName, &objeto, &tabela->esquema);
	strcpy(tabela->nome, nomeTabela->tableName);

	for(i=0; i < nomeTabela->N; i++) {
		colunas = insereValor(tabela, colunas, nomeTabela->columnName[i], nomeTabela->values[i]);
	}

	if(finalizaInsert(nomeTabela->tableName, colunas) == SUCCESS) {
		printf("INSERT 0 1\n");
	} 



    return 0;
}
