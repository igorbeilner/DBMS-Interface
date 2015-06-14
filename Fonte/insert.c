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

			if(s_insert->type[i] == 'S' && type == 'C') {
				s_insert->values[i][1] = '\0';
				s_insert->type[i] = 'C';
			}

			if(s_insert->type[i] == 'D' && type == 'I') {
				s_insert->values[i][procuraPonto(s_insert->values[i])] = '\0';
				s_insert->type[i] = 'D';
			}

			if(!type) 		//verifica se a coluna foi encontrada
				printf("Nome da coluna invalido\n");
			else if(s_insert->type[i] == type)	//verifica se o dado inserido e do mesmo tipo que o aceito pela coluna
				colunas = insereValor(tabela, colunas, s_insert->columnName[i], s_insert->values[i]);
			else {
				printf("Tipo de dados invalido para a coluna\n");
				return; 
			}
		}    
	} else {
		for(i=0; i < objeto.qtdCampos; i++) {

			if(s_insert->type[i] == 'S' && tabela->esquema[i].tipo == 'C') {
				s_insert->values[i][1] = '\0';
				s_insert->type[i] = 'C';
			}

			if(s_insert->type[i] == 'I' && tabela->esquema[i].tipo == 'D') {

				s_insert->values[i][procuraPonto(s_insert->values[i])] = '\0';
				s_insert->type[i] = 'D';
			}

			if(s_insert->type[i] == tabela->esquema[i].tipo)
				colunas = insereValor(tabela, colunas, tabela->esquema[i].nome, s_insert->values[i]);
			else {
				printf("Tipo de dados invalido para a coluna %d\n", i);
				return;
			}
		}
	}
	if(finalizaInsert(s_insert->tableName, colunas) == SUCCESS)
		printf("INSERT 0 1\n");

}
