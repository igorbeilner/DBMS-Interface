#include <stdlib.h>
#include <string.h>
#include "buffend.h"
#include "interface/y.tab.h"


int main(){
    dbInit();
    printf("Você está utilizando o Ibetres. Digite \"help\" caso necessite de ajuda.\n");
    interface();
    printf("Desconectado.\n");
    return 0;
}
