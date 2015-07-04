#include <stdlib.h>
#include <string.h>
#include "buffend.h"
#include "interface/y.tab.h"


int main(){
    dbInit();
    printf("Bem-vindo! Utilize \\c <nome_banco> para conectar.\n");
    interface();
    printf("Desconectado.\n");
    return 0;
}
