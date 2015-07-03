//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Verifica a existência do atributo antes de adicionar na tabela
    Parametros: Nome da tabela, coluna C.
    Retorno:    INT
                SUCCESS,
                ERRO_DE_PARAMETRO
   ---------------------------------------------------------------------------------------------*/

int existeAtributo(char *nomeTabela, column *c){
    int erro, x, count;
    struct fs_objects objeto;
    memset(&objeto, 0, sizeof(struct fs_objects));
    tp_table *tabela;
    tp_buffer *bufferpoll;
    column *aux;

    if(iniciaAtributos(&objeto, &tabela, &bufferpoll, nomeTabela) != SUCCESS)
        return ERRO_DE_PARAMETRO;

    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, tabela, objeto);

    column *pagina = getPage(bufferpoll, tabela, objeto, 0);

    if(pagina == NULL){
        pagina = getPage(bufferpoll, tabela, objeto, 1);
    }

    if(pagina != NULL){
        count = 0;
        for(x = 0; x < objeto.qtdCampos; x++){
            if (!pagina[x].nomeCampo) continue;
            for(aux = c; aux != NULL; aux=aux->next) {
                if (!aux->nomeCampo) continue;
                if(strcmp(pagina[x].nomeCampo, aux->nomeCampo) == 0)
                    count++;
            }
        }
        if(count != objeto.qtdCampos){
            return ERRO_DE_PARAMETRO;
        }
    }

    return SUCCESS;
}