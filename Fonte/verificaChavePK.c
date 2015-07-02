//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Gera as verificações em relação a chave PK.
    Parametros: Nome da Tabela, Coluna C, Nome do Campo, Valor do Campo
    Retorno:    INT
                SUCCESS,
                ERRO_DE_PARAMETRO,
                ERRO_CHAVE_PRIMARIA
   ---------------------------------------------------------------------------------------------*/

int verificaChavePK(char *nomeTabela, column *c, char *nomeCampo, char *valorCampo) {
    printf("in\n");
    int j, x, erro, page;

    struct fs_objects objeto;
    tp_table *tabela;
    tp_buffer *bufferpoll;

    erro = existeAtributo(nomeTabela, c);
    if (erro != SUCCESS )
        return ERRO_DE_PARAMETRO;


    if (iniciaAtributos(&objeto, &tabela, &bufferpoll, nomeTabela) != SUCCESS)
        return ERRO_DE_PARAMETRO;

    printf("1\n");
    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, tabela, objeto);

    page = 0;
    for (page = 0; page < PAGES; page++) {
        column *pagina = getPage(bufferpoll, tabela, objeto, page);

        for(j = 0; j < objeto.qtdCampos * bufferpoll[0].nrec; j++){

            if (strcmp(pagina[j].nomeCampo, nomeCampo) == 0) {
                printf("Verificando campo: %s\n", nomeCampo);

                if (pagina[j].tipoCampo == 'S') {
                    if (strcmp(pagina[j].valorCampo, valorCampo) == 0){
                        return ERRO_CHAVE_PRIMARIA;
                    }
                } else if (pagina[j].tipoCampo == 'I') {
                    int *n = (int *)&pagina[j].valorCampo[0];

                    printf("Comparando: %d == %d\n", *n, atoi(valorCampo));
                    if (*n == atoi(valorCampo)) {
                        return ERRO_CHAVE_PRIMARIA;
                    }
                } else if (pagina[j].tipoCampo == 'D'){
                    double *nn = (double *)&pagina[j].valorCampo[0];

                    if (*nn == atof(valorCampo)){
                        return ERRO_CHAVE_PRIMARIA;
                    }
                } else if (pagina[j].tipoCampo == 'C'){
                    if (pagina[j].valorCampo == valorCampo){
                        return ERRO_CHAVE_PRIMARIA;
                    }
                }
            }
        }
    }

    printf("out\n");
    return SUCCESS;
}