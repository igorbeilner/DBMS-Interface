//BufferPool
#include "buffend.h"

int finalizaInsert(char *nome, column *c){
    column *auxC, *temp;
    int i = 0, x = 0, t, erro, j = 0;
    FILE *dados;

    struct fs_objects objeto,dicio; // Le dicionario
    tp_table *auxT ; // Le esquema
    auxT = abreTabela(nome, &dicio, &auxT);

    table *tab     = (table *)malloc(sizeof(table));
    tp_table *tab2 = (tp_table *)malloc(sizeof(struct tp_table));

    tab->esquema = abreTabela(nome, &objeto, &tab->esquema);
    tab2 = procuraAtributoFK(objeto);

    for(j = 0, temp = c; j < objeto.qtdCampos && temp != NULL; j++, temp = temp->next){
        switch(tab2[j].chave){
            case NPK:
                erro = SUCCESS;
                break;

            case PK:
                erro = verificaChavePK(nome, temp , temp->nomeCampo, temp->valorCampo);
                if (erro == ERRO_CHAVE_PRIMARIA){
                    printf("error: Chave primária duplicada na coluna '%s'. O valor '%s' já existe. Nenhum registro inserido.\n", temp->nomeCampo, temp->valorCampo);
                    free(c);    // Libera a memoria da estrutura.
					free(auxT); // Libera a memoria da estrutura.
					//free(temp); // Libera a memoria da estrutura.
					free(tab); // Libera a memoria da estrutura.
					free(tab2); // Libera a memoria da estrutura.
                    return ERRO_CHAVE_PRIMARIA;
                }

                break;

            case FK:
                if (tab2[j].chave == 2 && strlen(tab2[j].attApt) != 0 && strlen(tab2[j].tabelaApt) != 0){

                    erro = verificaChaveFK(nome, temp, tab2[j].nome, temp->valorCampo, tab2[j].tabelaApt, tab2[j].attApt);

                    if (erro != SUCCESS){
                        printf("error: Referência inválida para '%s.%s'. Não existe o valor '%s'. Nenhum registro inserido.\n", tab2[j].tabelaApt,tab2[j].attApt,temp->valorCampo);
                        free(c);    // Libera a memoria da estrutura.
						free(auxT); // Libera a memoria da estrutura.
						free(temp); // Libera a memoria da estrutura.
                        free(tab); // Libera a memoria da estrutura.
						free(tab2); // Libera a memoria da estrutura.
                        return ERRO_CHAVE_ESTRANGEIRA;
                    }
                }

                break;
        }
    }


    if (erro == ERRO_CHAVE_ESTRANGEIRA){
        printf("error: Erro desconhecido de chave estrangeira. Nenhum registro inserido.\n");
        free(c);    // Libera a memoria da estrutura.
		free(auxT); // Libera a memoria da estrutura.
		free(temp); // Libera a memoria da estrutura.
        free(tab); // Libera a memoria da estrutura.
		free(tab2); // Libera a memoria da estrutura.
        return ERRO_CHAVE_ESTRANGEIRA;
    }

    if (erro == ERRO_CHAVE_PRIMARIA){
        printf("error: Erro desconhecido de chave primária. Nenhum registro inserido.\n");
        free(c);    // Libera a memoria da estrutura.
		free(auxT); // Libera a memoria da estrutura.
		free(temp); // Libera a memoria da estrutura.
        free(tab); // Libera a memoria da estrutura.
		free(tab2); // Libera a memoria da estrutura.
        return ERRO_CHAVE_PRIMARIA;
    }
    if (erro == ERRO_DE_PARAMETRO) {
        printf("error: Parâmetro inválido. Nenhum registro inserido.\n");
        free(c);    // Libera a memoria da estrutura.
		free(auxT); // Libera a memoria da estrutura.
		free(temp); // Libera a memoria da estrutura.
        free(tab); // Libera a memoria da estrutura.
		free(tab2); // Libera a memoria da estrutura.
        return ERRO_DE_PARAMETRO;
    }


    if((dados = fopen(dicio.nArquivo,"a+b")) == NULL){
		free(c);    // Libera a memoria da estrutura.
        printf("error: Erro ao abrir arquivo. Nenhum registro inserido.\n");
		free(auxT); // Libera a memoria da estrutura.
		free(temp); // Libera a memoria da estrutura.
        free(tab); // Libera a memoria da estrutura.
		free(tab2); // Libera a memoria da estrutura.
        return ERRO_ABRIR_ARQUIVO;

	}

    for(auxC = c, t = 0; auxC != NULL; auxC = auxC->next, t++){
        if (t >= dicio.qtdCampos)
            t = 0;

        if (auxT[t].tipo == 'S'){ // Grava um dado do tipo string.

            if (sizeof(auxC->valorCampo) > auxT[t].tam && sizeof(auxC->valorCampo) != 8){
                printf("error: O tamanho da string não é válido. Nenhum registro inserido.\n");
				free(tab); // Libera a memoria da estrutura.
				free(tab2); // Libera a memoria da estrutura.
				free(c);    // Libera a memoria da estrutura.
				free(auxT); // Libera a memoria da estrutura.
				free(temp); // Libera a memoria da estrutura.
				fclose(dados);
                return ERRO_NO_TAMANHO_STRING;
            }

            if (strcmp(auxC->nomeCampo, auxT[t].nome) != 0){
                printf("error: O nome do campo '%s' é inválido. Nenhum registro inserido.\n", auxC->nomeCampo);
				free(tab); // Libera a memoria da estrutura.
				free(tab2); // Libera a memoria da estrutura.
				free(c);    // Libera a memoria da estrutura.
				free(auxT); // Libera a memoria da estrutura.
				free(temp); // Libera a memoria da estrutura.
				fclose(dados);
                return ERRO_NOME_CAMPO;
            }

            char valorCampo[auxT[t].tam];
            strcpy(valorCampo, auxC->valorCampo);
            strcat(valorCampo, "\0");
            fwrite(&valorCampo,sizeof(valorCampo),1,dados);

        } else if (auxT[t].tipo == 'I'){ // Grava um dado do tipo inteiro.
            i = 0;
            while (i < strlen(auxC->valorCampo)){
                if (auxC->valorCampo[i] < 48 || auxC->valorCampo[i] > 57){
                    printf("error: Valor inteiro esperado para a coluna '%s'. Nenhum registro inserido.\n", auxC->nomeCampo);
					free(tab); // Libera a memoria da estrutura.
					free(tab2); // Libera a memoria da estrutura.
					free(c);    // Libera a memoria da estrutura.
					free(auxT); // Libera a memoria da estrutura.
					//free(temp); // Libera a memoria da estrutura.
					fclose(dados);
                    return ERRO_NO_TIPO_INTEIRO;
                }
                i++;
            }

            int valorInteiro = 0;

            sscanf(auxC->valorCampo,"%d",&valorInteiro);
            fwrite(&valorInteiro,sizeof(valorInteiro),1,dados);

        } else if (auxT[t].tipo == 'D'){ // Grava um dado do tipo double.
            x = 0;
            while (x < strlen(auxC->valorCampo)){
                if((auxC->valorCampo[x] < 48 || auxC->valorCampo[x] > 57) && (auxC->valorCampo[x] != 46)){
                    printf("error: Valor do tipo double esperado para a coluna '%s'. Nenhum registro inserido.\n", auxC->nomeCampo);
					free(tab); // Libera a memoria da estrutura.
					free(tab2); // Libera a memoria da estrutura.
					free(c);    // Libera a memoria da estrutura.
					free(auxT); // Libera a memoria da estrutura.
					free(temp); // Libera a memoria da estrutura.
					fclose(dados);
                    return ERRO_NO_TIPO_DOUBLE;
                }
                x++;
            }

            double valorDouble = convertD(auxC->valorCampo);
            fwrite(&valorDouble,sizeof(valorDouble),1,dados);
        }
        else if (auxT[t].tipo == 'C'){ // Grava um dado do tipo char.

            if (strlen(auxC->valorCampo) > (sizeof(char))) {
                printf("error: Caractere único esperado para a coluna '%s'. Nenhum registro inserido.\n", auxC->nomeCampo);
				free(tab); // Libera a memoria da estrutura.
				free(tab2); // Libera a memoria da estrutura.
				free(c);    // Libera a memoria da estrutura.
				free(auxT); // Libera a memoria da estrutura.
				free(temp); // Libera a memoria da estrutura.
				fclose(dados);
                return ERRO_NO_TIPO_CHAR;
            }
            char valorChar = auxC->valorCampo[0];
            fwrite(&valorChar,sizeof(valorChar),1,dados);
        }

    }

    fclose(dados);
    free(tab); // Libera a memoria da estrutura.
	free(tab2); // Libera a memoria da estrutura.
    free(c);    // Libera a memoria da estrutura.
    free(auxT); // Libera a memoria da estrutura.
    free(temp); // Libera a memoria da estrutura.
    return SUCCESS;
}