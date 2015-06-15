//BufferPool
#include "buffend.h"

char retornaTamanhoTipoDoCampo(char *nomeCampo, table  *tab) {
	char *auxNomeParam, *auxNomeStruct;

	char tipo = 0;

	tp_table *temp = tab->esquema;

	auxNomeParam = (char *)malloc((strlen(nomeCampo)+1)*sizeof(char));
	strcpy(auxNomeParam, nomeCampo);

	while(temp != NULL) {
		auxNomeStruct = (char *)malloc((strlen(temp->nome)+1)*sizeof(char));
		strcpy(auxNomeStruct, temp->nome);

		if (strcmp(toUppercase(auxNomeParam),toUppercase(auxNomeStruct)) == 0) {
			tipo = temp->tipo;

			free(auxNomeStruct);
			free(auxNomeParam);
			return tipo;
		}

		free(auxNomeStruct);
		temp = temp->next;
	}

	free(auxNomeParam);
	return tipo;
}
