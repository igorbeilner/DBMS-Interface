#include "buffend.h"


void insert(rc_insert *s_insert) {

	int i;
	table *tabela = (table *)malloc(sizeof(table));
	column *colunas = NULL;
	struct fs_objects objeto;
	char type;

	abreTabela(s_insert->tableName, &objeto, &tabela->esquema); //retorna o esquema para a insere valor
	strcpy(tabela->nome, s_insert->tableName);

	if(s_insert->columnName != NULL) {
		for(i=0; i < s_insert->N; i++) {
			
			type = retornaTamanhoTipoDoCampo(s_insert->columnName[i], tabela);
			if(!type) 
				printf("Nome da coluna invalido\n");
			else if(s_insert->type[i] == type)
				colunas = insereValor(tabela, colunas, s_insert->columnName[i], s_insert->values[i]);
			else {
				printf("Tipo de dados invalido para a coluna\n");
				return;
			}
		}
	} else {
		for(i=0; i < objeto.qtdCampos; i++) {
			if(s_insert->type[i] == tabela->esquema->tipo)
				colunas = insereValor(tabela, colunas, tabela->esquema[i].nome, s_insert->values[i]);
			else {
				printf("Tipo de dados invalido para a coluna\n");
				return;
			}
		}
	}
	if(finalizaInsert(s_insert->tableName, colunas) == SUCCESS)
		printf("INSERT 0 1\n");

}
