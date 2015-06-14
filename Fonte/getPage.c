//BufferPool
#include "buffend.h"

// RETORNA PAGINA DO BUFFER
column * getPage(tp_buffer *buffer, tp_table *campos, struct fs_objects objeto, int page){
    
    if(page >= PAGES)
        return ERRO_PAGINA_INVALIDA;

    //if(buffer[page].nrec == 0) //Essa página não possui registros
        //return ERRO_PARAMETRO;
    
    column *colunas = (column *)malloc(sizeof(column)*objeto.qtdCampos*buffer[page].nrec); //Aloca a quantidade de campos necessária
    
    if(colunas == NULL)
        return ERRO_DE_ALOCACAO;
    
    int i=0, j=0, t=0, h=0;
        
    while(i < buffer[page].position){
        t=0;
        if(j >= objeto.qtdCampos)
            j=0;
        colunas[h].valorCampo = (char *)malloc(sizeof(char)*campos[j].tam);
        colunas[h].tipoCampo = campos[j].tipo;  //Guarda tipo do campo
        strcpy(colunas[h].nomeCampo, campos[j].nome); //Guarda nome do campo
         
        while(t < campos[j].tam){
            colunas[h].valorCampo[t] = buffer[page].data[i]; //Copia os dados
            t++;
            i++;
        }
        h++;
        j++;
    }
    return colunas; //Retorna a 'page' do buffer
}