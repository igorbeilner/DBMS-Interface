#include "buffend.h"

int typesCompatible(char table_type, char insert_type) {
	return (table_type == 'D' && insert_type == 'I')
		|| (table_type == 'S' && insert_type == 'I')
		|| (table_type == 'C' && insert_type == 'I')
		|| (table_type == 'S' && insert_type == 'D')
		|| (table_type == 'S' && insert_type == 'C')
		|| (table_type == 'D' && insert_type == 'D')
		|| (table_type == 'I' && insert_type == 'I')
		|| (table_type == 'S' && insert_type == 'S')
		|| (table_type == 'C' && insert_type == 'C');

}

// Busca o valor da coluna. Assume que columnName foi preenchido.
char *getInsertedValue(rc_insert *s_insert, char *columnName, table *tabela) {
	int i;
	char tipo, *noValue;

	for (i = 0; i < s_insert->N; i++) {
		if (strcmp(s_insert->columnName[i], columnName) == 0) {
			return s_insert->values[i];
		}
	}

	tipo = retornaTamanhoTipoDoCampo(columnName, tabela);
	noValue = (char *)malloc(sizeof(char)*3);

	if (tipo == 'I') {
		noValue = "0";
	} else if (tipo == 'D') {
		noValue = "0.0";
	} else
		noValue[0] = '\0';

	return noValue;
}

char getInsertedType(rc_insert *s_insert, char *columnName, table *tabela) {
	int i;
	char noValue;
	for (i = 0; i < s_insert->N; i++) {
		if (strcmp(s_insert->columnName[i], columnName) == 0) {
			return s_insert->type[i];
		}
	}

	noValue = retornaTamanhoTipoDoCampo(columnName, tabela);

	return noValue;
}

void insert(rc_insert *s_insert) {

	int i;
	table *tabela = (table *)malloc(sizeof(table));
	column *colunas = NULL;
	tp_table *esquema;
	struct fs_objects objeto;
	char  flag=0;

	abreTabela(s_insert->tableName, &objeto, &tabela->esquema); //retorna o esquema para a insere valor
	strcpy(tabela->nome, s_insert->tableName);

	if(s_insert->columnName != NULL) {
		for (esquema = tabela->esquema; esquema != NULL; esquema = esquema->next) {
			if(typesCompatible(esquema->tipo,getInsertedType(s_insert, esquema->nome, tabela))) {
				colunas = insereValor(tabela, colunas, esquema->nome, getInsertedValue(s_insert, esquema->nome, tabela));
			} else {
				printf("Tipo de dados invalido para a coluna '%s' da tabela '%s' (esperado: %c, recebido: %c)\n", esquema->nome, tabela->nome, esquema->tipo, getInsertedType(s_insert, esquema->nome, tabela));
				flag=1;
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
				printf("Tipo de dados invalido para a coluna '%s' da tabela '%s' (esperado: %c, recebido: %c)\n", tabela->esquema[i].nome, tabela->nome, tabela->esquema[i].tipo, s_insert->type[i]);
				flag=1;
			}
		}
	}

	if(!flag)
		if(finalizaInsert(s_insert->tableName, colunas) == SUCCESS)
			printf("INSERT 0 1\n");

}
