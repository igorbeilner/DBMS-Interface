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
    int erro, x;
    struct fs_objects objeto; 
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
        erro = SUCCESS;
        for(x = 0; x < objeto.qtdCampos; x++){
            for(aux = c; aux != NULL; aux=aux->next){
                if(strcmp(pagina[x].nomeCampo, aux->nomeCampo) == 0)
                    erro++;
            }
        }
        if(erro != objeto.qtdCampos){
            return ERRO_DE_PARAMETRO;
        }
    }
 
    return SUCCESS; 
}