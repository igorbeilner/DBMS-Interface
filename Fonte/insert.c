#include "buffend.h"


int insert(rc_insert *s_insert) {

	int i;
	table *tabela = (table *)malloc(sizeof(tabela));
	column *colunas = NULL;
	struct fs_objects objeto;

	abreTabela(s_insert->tableName, &objeto, &tabela->esquema); //retorna o esquema para a insere valor
	strcpy(tabela->nome, s_insert->tableName);

	if(s_insert->columnName != NULL)
		for(i=0; i < s_insert->N; i++)
			colunas = insereValor(tabela, colunas, s_insert->columnName[i], s_insert->values[i]);
	else
		for(i=0; i < objeto.qtdCampos; i++)
			colunas = insereValor(tabela, colunas, tabela->esquema[i].nome, s_insert->values[i]);

	if(finalizaInsert(s_insert->tableName, colunas) == SUCCESS)
		printf("INSERT 0 1\n");

    return 0;
}
