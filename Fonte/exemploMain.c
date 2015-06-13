#include <stdlib.h>
#include <string.h>
#include "buffend.h"
#include "interface/y.tab.h"


int main(){
    int nrTabelas = 3;
    int nTabela[nrTabelas];
    table  *tab[nrTabelas];
    column *colunas;
    int object, schema;

    object      = existeArquivo("fs_object.dat");
    schema      = existeArquivo("fs_schema.dat");
    nTabela[0]  = existeArquivo("Aluno.dat");
    nTabela[1]  = existeArquivo("Inst.dat");
    nTabela[2]  = existeArquivo("Inscri.dat");
     if(!object || !schema){

        if(!nTabela[0]){                                                                    //Se ainda não existe a Aluno, a mesma é criada
            tab[0] = iniciaTabela("Aluno");                                                 //Cria a tabela
            tab[0] = adicionaCampo(tab[0], "CPF"     , 'I', (sizeof(int))   ,PK,"","");     //Cria os atributos
            tab[0] = adicionaCampo(tab[0], "Nome"    , 'S', 20              ,NPK,"","");
            tab[0] = adicionaCampo(tab[0], "Endereco", 'S', 20              ,NPK,"","");
            tab[0] = adicionaCampo(tab[0], "Peso"    , 'D', (sizeof(double)),NPK,"","");
            finalizaTabela(tab[0]);
         }
         if(!nTabela[1]){
            tab[1] = iniciaTabela("Inst");
            tab[1] = adicionaCampo(tab[1], "CodInst"  , 'I', (sizeof(int))   ,PK , "","");
            tab[1] = adicionaCampo(tab[1], "Nome"     , 'S', 20              ,NPK, "","");
            tab[1] = adicionaCampo(tab[1], "Endereco" , 'S', 20              ,NPK, "","");
            tab[1] = adicionaCampo(tab[1], "Reitor"   , 'S', 10              ,NPK, "","");
            finalizaTabela(tab[1]);
        }
        if(!nTabela[2]){
            tab[2] = iniciaTabela("Inscri");
            tab[2] = adicionaCampo(tab[2], "CodMat"     , 'I', (sizeof(int))  ,PK, "","");
            tab[2] = adicionaCampo(tab[2], "CPF"        , 'I', (sizeof(int))  ,FK, "Aluno","CPF");
            tab[2] = adicionaCampo(tab[2], "CodInst"    , 'I', (sizeof(int))  ,FK , "Inst","CodInst");
            tab[2] = adicionaCampo(tab[2], "Curso"   , 'S',  20  ,NPK, "","");
            finalizaTabela(tab[2]);
        }

      /*  rc_insert teste;

        teste.tableName = (char *)malloc(100 * sizeof(char));
        //teste.columnName = (char **)malloc(100 * sizeof(char));
        teste.values = (char **)malloc(100 * sizeof(char));

        int i;
        for(i=0; i<100; i++) {
            //teste.columnName[i] = (char *)malloc(100 * sizeof(char));
            teste.values[i] = (char *)malloc(100 * sizeof(char));
        }

        strcpy(teste.tableName, "Aluno");
        teste.tableName[5] = '\0';*/
        /*strcpy(teste.columnName[0], "CPF");
        strcpy(teste.columnName[1], "Nome");
        strcpy(teste.columnName[2], "Endereco");
        strcpy(teste.columnName[3], "Peso");*/

       /* strcpy(teste.values[0], "123456");
        strcpy(teste.values[1], "Rogerio");
        strcpy(teste.values[2], "Rua Marechal");
        strcpy(teste.values[3], "81.4");

        teste.columnName[0][3] = '\0';
        teste.columnName[1][4] = '\0';
        teste.columnName[2][8] = '\0';
        teste.columnName[3][4] = '\0';*/
      /*teste.values[0][6] = '\0';
        teste.values[1][7] = '\0';
        teste.values[2][12] = '\0';
        teste.values[3][4] = '\0';

        teste.N = 4;

        insert(&teste);*/

        printf("Conectando...\n");
        printf("Conectado!\n"); // hahaha
        interface();
        printf("Desconectado.\n");
        // INSERT INTO Aluno (CPF, Nome, Endereco, Peso) VALUES (123456, Rogerio, RuaMarechal, 80);
        // INSERT INTO Aluno VALUES (123456, Rogerio, RuaMarechal, 80);

        /*
         //Inserção de tuplas na tabela1
        colunas = NULL;
        colunas = insereValor(tab[0],colunas, "CPF", "123456");
        colunas = insereValor(tab[0],colunas, "Nome", "Rogerio");
        colunas = insereValor(tab[0],colunas, "Endereco", "Rua Marechal");
        colunas = insereValor(tab[0],colunas, "Peso", "81.4");
        finalizaInsert("Aluno", colunas);

        colunas = NULL;
        colunas = insereValor(tab[0],colunas, "CPF", "654321");
        colunas = insereValor(tab[0],colunas, "Nome", "Ricardo");
        colunas = insereValor(tab[0],colunas, "Endereco", "RuaClevela");
        colunas = insereValor(tab[0],colunas, "Peso", "88.9");
        finalizaInsert("Aluno", colunas);

        colunas = NULL;
        colunas = insereValor(tab[0],colunas, "CPF", "1234567");
        colunas = insereValor(tab[0],colunas, "Nome", "Natan");
        colunas = insereValor(tab[0],colunas, "Endereco", "RuaDelmi");
        colunas = insereValor(tab[0],colunas, "Peso", "58.9");
        finalizaInsert("Aluno", colunas); */


        //Inserção de tuplas na tabela2
        colunas = NULL;
        colunas = insereValor(tab[1],colunas, "CodInst", "111");
        colunas = insereValor(tab[1],colunas, "Nome", "UFFS");
        colunas = insereValor(tab[1],colunas, "Endereco", "RuadeTerra");
        colunas = insereValor(tab[1],colunas, "Reitor", "MandaChuva");
        finalizaInsert("Inst", colunas);

        colunas = NULL;
        colunas = insereValor(tab[1],colunas, "CodInst", "222");
        colunas = insereValor(tab[1],colunas, "Nome", "CEFET");
        colunas = insereValor(tab[1],colunas, "Endereco", "RuadePedra");
        colunas = insereValor(tab[1],colunas, "Reitor", "MandaVento");
        finalizaInsert("Inst", colunas);

        colunas = NULL;
        colunas = insereValor(tab[1],colunas, "CodInst", "333");
        colunas = insereValor(tab[1],colunas, "Nome", "UNOESC");
        colunas = insereValor(tab[1],colunas, "Endereco", "RuadeAsfal");
        colunas = insereValor(tab[1],colunas, "Reitor", "MandaAgua");
        finalizaInsert("Inst", colunas);



        //Inserção de tupla na tabela3
        colunas = NULL;
        colunas = insereValor(tab[2],colunas, "CodMat", "1401");
        colunas = insereValor(tab[2],colunas, "CPF", "123456");
        colunas = insereValor(tab[2],colunas, "CodInst", "333");
        colunas = insereValor(tab[2],colunas, "Curso", "CC");
        finalizaInsert("Inscri", colunas);
        /*
        colunas = NULL;
        colunas = insereValor(tab[2],colunas, "CodMat", "1402");
        colunas = insereValor(tab[2],colunas, "CPF", "654321");
        colunas = insereValor(tab[2],colunas, "CodInst", "222");
        colunas = insereValor(tab[2],colunas, "Curso", "CC");
        finalizaInsert("Inscri", colunas);

        colunas = NULL;
        colunas = insereValor(tab[2],colunas, "CodMat", "1403");
        colunas = insereValor(tab[2],colunas, "CPF", "1234567");
        colunas = insereValor(tab[2],colunas, "CodInst", "111");
        colunas = insereValor(tab[2],colunas, "Curso", "ADM");
        finalizaInsert("Inscri", colunas);*/

    }


    imprime("Aluno");        //Imprime os atributos da tabela "Aluno"
    excluirTabela("Aluno");
    imprime("Inst");
    excluirTabela("Inst");   //Exclui os dados da tabela do dicionario e remove-a do disco
    imprime("Inscri");
    excluirTabela("Inscri");


    return 0;
}
