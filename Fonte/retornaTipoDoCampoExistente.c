#include "buffend.h"

char retornaTipoDoCampoExistente(table *tabela, char *nome) {
	tp_table *esq;

	for (esq = tabela->esquema; esq != NULL; esq = esq->next) {
		if (strcmp(esq->nome, nome) == 0) {
			return esq->tipo;
		}
	}

	return 0;
}