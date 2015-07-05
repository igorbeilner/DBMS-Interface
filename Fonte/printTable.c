//BufferPool
#include "buffend.h"

/*------------------------------------------------------------------------------------------
Objetivo: Mostrar as tabelas do banco de dados ou, em específico, os atributos de uma tabela
------------------------------------------------------------------------------------------*/

void printTable(char *tbl){
	if(tbl == NULL){     //mostra todas as tabelas do banco
		FILE *dicionario;
		printf("		List of Relations\n");
		char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);

		char directory[LEN_DB_NAME*2];
    	strcpy(directory, connected.db_directory);
    	strcat(directory, "fs_object.dat");

		if((dicionario = fopen(directory,"a+b")) == NULL){
			free(tupla);
			exit(1);
		}

		printf(" %-10s | %-10s | %-10s | %-10s\n", "Schema", "Name", "Type", "Owner");
		printf("------------+------------+------------+-------\n");
		while(fgetc (dicionario) != EOF){
			fseek(dicionario, -1, 1);
			fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, dicionario);
			printf(" %-10s | %-10s | %-10s | %-10s\n", "public", tupla, "tuple", "ibetres");
			fseek(dicionario, 28, 1);
		}
		fclose(dicionario);
		free(tupla);
		printf("\n\n");
	} else{               //mostra todos atributos da tabela *tbl

		if(!verificaNomeTabela(tbl)) {
			printf("Did not find any relation named \"%s\".\n", tbl);
			return;
		}

		printf("Table: public.%s\n", tbl);
		printf(" Column    | Type\n");
		printf("----------------------\n");


		struct fs_objects objeto1;
		tp_table *esquema1;

		abreTabela(tbl, &objeto1, &esquema1);

		tp_table *tab3 = (tp_table *)malloc(sizeof(struct tp_table));
		tab3 = procuraAtributoFK(objeto1);

		int l;
		for(l=0; l<objeto1.qtdCampos; l++) {

			printf(" %s%-10s|", ((tab3[l].chave == PK)? "*":" "), tab3[l].nome);

			if(tab3[l].tipo == 'S')
				printf(" varchar(%d)\n", tab3[l].tam);
			else if(tab3[l].tipo == 'I')
				printf(" integer\n");
			else if(tab3[l].tipo == 'C')
				printf(" char\n");
			else if(tab3[l].tipo == 'D')
				printf(" double\n");
		}
		free(tab3);
		printf("\n\n");
	}
}
