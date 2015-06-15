//BufferPool
#include "buffend.h"

/*------------------------------------------------------------------------------------------
Objetivo: Mostrar as tabelas do banco de dados ou, em específico, os atributos de uma tabela
------------------------------------------------------------------------------------------*/

void printTable(char *tbl){
	if(tbl == NULL){     //mostra todas as tabelas do banco
		FILE *dicionario;
		printf(" Tabelas da base de dados:\n");
		printf("---------------------------\n");
		char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
		if((dicionario = fopen("fs_object.dat","a+b")) == NULL){
			free(tupla);
			exit(1);
		}

		while(fgetc (dicionario) != EOF){
			fseek(dicionario, -1, 1);
			fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, dicionario);
			printf(" %s\n", tupla);
			fseek(dicionario, 28, 1);
		}
		fclose(dicionario);
		free(tupla);
		printf("\n\n");
	} else{               //mostra todos atributos da tabela *tbl

		if(!verificaNomeTabela(tbl)) {
			printf("Nome da tabela invalido!\n");
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

			printf(" %-10s|", tab3[l].nome);

			if(tab3[l].tipo == 'S')
				printf(" text\n");
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


