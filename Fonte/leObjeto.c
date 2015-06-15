//BufferPool
#include "buffend.h"

struct fs_objects leObjeto(char *nTabela){

    FILE *dicionario;
    char *tupla = (char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    int cod;
    dicionario = fopen("fs_object.dat", "a+b"); // Abre o dicionario de dados.

    struct fs_objects objeto;

    if(!verificaNomeTabela(nTabela)){
        printf("Erro GRAVE! na função leObjeto(). Nome da tabela inválido.\n");
        if (dicionario)
            fclose(dicionario);
        free(tupla);
    }

    if (dicionario == NULL) {
        printf("Erro GRAVE! na função leObjeto(). Arquivo não encontrado.\n\n");
        free(tupla);
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