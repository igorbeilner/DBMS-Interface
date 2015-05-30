//BufferPool
#include "buffend.h"

/* ---------------------------------------------------------------------------------------------- 
    Objetivo:   Utilizada para impressão de tabelas.
    Parametros: Nome da tabela (char).    
    Retorno:    void.
   ---------------------------------------------------------------------------------------------*/
    
void imprime(char nomeTabela[]) {

    int j,erro, x, p;
    struct fs_objects objeto = leObjeto(nomeTabela);    
    
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
    printf("Número de tuplas: %d\n", --x);
	p = 0;
	while(x){
	    column *pagina = getPage(bufferpoll, esquema, objeto, p);	
	    if(pagina == ERRO_PARAMETRO){
            printf("Erro GRAVE ao abrir a TABELA.\nAbortando...\n");
            exit(1);
	    }
		for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){
        	if(pagina[j].tipoCampo == 'S')
            	printf("%s: %-15s ", pagina[j].nomeCampo,pagina[j].valorCampo);
        	else if(pagina[j].tipoCampo == 'I'){
            	int *n = (int *)&pagina[j].valorCampo[0];
            	printf("%s: %-15d ",pagina[j].nomeCampo, *n);
        	} else if(pagina[j].tipoCampo == 'C'){
            	printf("%s: %-15c ",pagina[j].nomeCampo, pagina[j].valorCampo[0]);
        	} else if(pagina[j].tipoCampo == 'D'){
            	double *n = (double *)&pagina[j].valorCampo[0];
   	        	 printf("%s: %-15f ",pagina[j].nomeCampo, *n);
        	}
        	if(j>=1 && ((j+1)%objeto.qtdCampos)==0){
            	printf("\n");
        	}
    	} 
    	x-=bufferpoll[p++].nrec;
    }
    printf("\n\n");
}