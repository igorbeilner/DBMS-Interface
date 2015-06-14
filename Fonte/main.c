#include <stdlib.h>
#include <string.h>
#include "buffend.h"
#include "interface/y.tab.h"


int main(){
    int nrTabelas = 3;
    int nTabela[nrTabelas];
    table  *tab[nrTabelas];
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

        printf("Bem vindo ao SGBD. Utilize CONNECT para conectar-se.\n");
        interface();
        printf("Desconectado.\n");
        // INSERT INTO Aluno (CPF, Nome, Endereco, Peso) VALUES (123456, Rogerio, RuaMarechal, 80);
        // INSERT INTO Aluno VALUES (123456, Rogerio, RuaMarechal, 80);

    }


    imprime("Aluno");           //Imprime os atributos da tabela
    imprime("Inst");
    imprime("Inscri");
    excluirTabela("Inscri");    //Exclui os dados da tabela do dicionario e remove-a do disco
    excluirTabela("Inst");
    excluirTabela("Aluno");


    return 0;
}
