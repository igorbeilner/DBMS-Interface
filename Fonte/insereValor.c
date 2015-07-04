//BufferPool
#include "buffend.h"

// INSERE NA TABELA
column *insereValor(table  *tab, column *c, char *nomeCampo, char *valorCampo) {
    int i;

    column *aux;
    if(c == NULL){ // Se o valor a ser inserido é o primeiro, adiciona primeiro campo.

        column *e = (column *)malloc(sizeof(column));

        if (e == NULL)    {
            return ERRO_DE_ALOCACAO;
        }

        int tam = retornaTamanhoValorCampo(nomeCampo, tab);
        char tipo = retornaTamanhoTipoDoCampo(nomeCampo,tab);

        int nTam = strlen(valorCampo);

        if (tipo == 'S') {
            nTam = tam;
        }

        e->valorCampo = (char *)malloc(sizeof(char) * (nTam+1));

        if (e->valorCampo == NULL) {
            return ERRO_DE_ALOCACAO;
        }

        int n = strlen(nomeCampo)+1;

        /**
         * Verifica se o nome ultrapassa o limite, se sim trunca
         */
        if (n > TAMANHO_NOME_CAMPO) {
           n = TAMANHO_NOME_CAMPO;
           printf("warning: Nome do campo excedeu o limite de tamanho e foi truncado.\n");
        }


        strncpylower(e->nomeCampo, nomeCampo, n-1);

        n = strlen(valorCampo);

        if (n > tam && tipo == 'S') {
            n = tam;
            printf("warning: O valor inserido na coluna '%s' excedeu o limite de tamanho e foi truncado.\n", nomeCampo);
        }

        for(i=0; i < n; i++) e->valorCampo[i] = valorCampo[i];
            e->valorCampo[i] = '\0';

        //strncpy(e->valorCampo, valorCampo,n);

        e->next = NULL;
        c = e;
        return c;
    } else {
        for(aux = c; aux != NULL; aux = aux->next) { // Anda até o final da lista de valores a serem inseridos e adiciona um novo valor.
            if(aux->next == NULL){

                column *e = (column *)malloc(sizeof(column));

                if (e == NULL) {
                    return ERRO_DE_ALOCACAO;
                }
                int tam = retornaTamanhoValorCampo(nomeCampo, tab);
                char tipo = retornaTamanhoTipoDoCampo(nomeCampo,tab);

                int nTam = strlen(valorCampo);

                if (tipo == 'S') {
                    nTam = tam;
                }

                e->valorCampo = (char *) malloc (sizeof(char) * (nTam+1));

                if (e->valorCampo == NULL) {
                    return ERRO_DE_ALOCACAO;
                }

                e->next = NULL;

                int n = strlen(nomeCampo)+1;

                /**
                 * Verifica se o nome do campo ultrapassa o limite, se sim trunca
                 */
                if (n > TAMANHO_NOME_CAMPO) {
                   n = TAMANHO_NOME_CAMPO;
                   printf("warning: Nome do campo excedeu o limite de tamanho e foi truncado.\n");
                }

                strncpylower(e->nomeCampo, nomeCampo, n-1);

                //strncpy(e->nomeCampo, nomeCampo,n);

                n = strlen(valorCampo);

                if (n > tam && tipo == 'S') {
                    n = tam;
                    printf("warning: O valor inserido na coluna '%s' excedeu o limite de tamanho e foi truncado.\n", nomeCampo);
                }

                for(i=0; i < n; i++) e->valorCampo[i] = valorCampo[i];
                e->valorCampo[i] = '\0';

                //strncpy(e->valorCampo, valorCampo,n);
                aux->next = e;
                return c;
            }
        }
    }

    return ERRO_INSERIR_VALOR;
}