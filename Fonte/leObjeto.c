//BufferPool
#include "buffend.h"

struct fs_objects leObjeto(char *nTabela){

    FILE *dicionario;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    int cod;
    dicionario = fopen("fs_object.dat", "a+b"); // Abre o dicionario de dados.

    struct fs_objects objeto;

    if(!verificaNomeTabela(nTabela)){
        printf("error: A tabela '%s' não foi encontrada.\n", nTabela);
        if (dicionario)
            fclose(dicionario);
        free(tupla);

        return objeto;
    }

    if (dicionario == NULL) {
        printf("error: Dicionário de dados não encontrado.\n\n");
        free(tupla);
        return objeto;
    }


    while(fgetc (dicionario) != EOF){
        fseek(dicionario, -1, 1);

        fread(tupla, sizeof(char), TAMANHO_NOME_TABELA , dicionario); //Lê somente o nome da tabela

        if(strcmp(tupla, nTabela) == 0){ // Verifica se o nome dado pelo usuario existe no dicionario de dados.
            strcpy(objeto.nome, tupla);
            fread(&cod,sizeof(int),1,dicionario);   // Copia valores referentes a tabela pesquisada para a estrutura.
            objeto.cod=cod;
            fread(tupla,sizeof(char),TAMANHO_NOME_TABELA,dicionario);
            strcpy(objeto.nArquivo, tupla);
            fread(&cod,sizeof(int),1,dicionario);
            objeto.qtdCampos = cod;

            free(tupla);
            return objeto;
        }
        fseek(dicionario, 28, 1); // Pula a quantidade de caracteres para a proxima verificacao(4B do codigo, 20B do nome do arquivo e 4B da quantidade de campos).
    }
    free(tupla);
    fclose(dicionario);

    return objeto;
}