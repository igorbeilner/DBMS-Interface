//BufferPool
#include "buffend.h"

/*------------------------------------------------------------------------------------------
Objetivo: Mostrar as tabelas do banco de dados ou, em específico, os atributos de uma tabela
------------------------------------------------------------------------------------------*/

void printTable(char *tbl){
    if(tbl == NULL){     //mostra todas as tabelas do banco
        FILE *dicionario;
        printf("Tabelas:\n");
        char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
        if((dicionario = fopen("fs_object.dat","a+b")) == NULL){
    		free(tupla);
            exit(1);
        }

        while(fgetc (dicionario) != EOF){
            fseek(dicionario, -1, 1);
            fread(tupla, sizeof(char), TAMANHO_NOME_TABELA, dicionario);
            printf("%s\n", tupla);
            fseek(dicionario, 28, 1);
        }
        fclose(dicionario);
        free(tupla);
    }
    else{               //mostra todos atributos da tabela *tbl

        int j,erro, x, p;
        struct fs_objects objeto = leObjeto(tbl);

        tp_table *esquema = leSchema(objeto);

        if(esquema == ERRO_ABRIR_ESQUEMA){
            printf("Erro GRAVE ao Criar o ESQUEMA.\n");
        }

        tp_buffer *bufferpoll = initbuffer();

        if(bufferpoll == ERRO_DE_ALOCACAO){
            printf("Erro GRAVE alocar memória para o BUFFER.\n");
        }

        erro = SUCCESS;
        for(x = 0; erro == SUCCESS; x++)
            erro = colocaTuplaBuffer(bufferpoll, x, esquema, objeto);

        column *pagina = getPage(bufferpoll, esquema, objeto, 0);

        if(pagina == ERRO_PARAMETRO){
            printf("Erro GRAVE ao abrir a TABELA.\n");
        }

        // PARA IMPRIMIR PÁGINA
        //printf("Número de tuplas: %d\n", --x);

        printf("Table: public.%s\n", tbl);
        printf(" Column     | Type\n");
        p = 0;
    	while(x){
    	    column *pagina = getPage(bufferpoll, esquema, objeto, p);
    	    if(pagina == ERRO_PARAMETRO){
                printf("Erro GRAVE ao abrir a TABELA.\nAbortando...\n");
                exit(1);
    	    }
    		for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){
            	if(pagina[j].tipoCampo == 'S')
                	printf("%s     | text\n", pagina[j].nomeCampo);
            	else if(pagina[j].tipoCampo == 'I'){
                	//int *n = (int *)&pagina[j].valorCampo[0];
                	printf("%s     | integer\n",pagina[j].nomeCampo);
            	} else if(pagina[j].tipoCampo == 'C'){
                	printf("%s     | char\n",pagina[j].nomeCampo);
            	} else if(pagina[j].tipoCampo == 'D'){
                	//double *n = (double *)&pagina[j].valorCampo[0];
            	    printf("%s     | double\n",pagina[j].nomeCampo);
            	}
            	//if(j>=1 && ((j+1)%objeto.qtdCampos)==0){
                //	printf("\n");
            	//}
        	}
        	x-=bufferpoll[p++].nrec;
        }
        printf("\n\n");
    }
}
