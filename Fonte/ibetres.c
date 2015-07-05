#include <stdlib.h>
#include <string.h>
#include "buffend.h"
#include "interface/y.tab.h"


int main(){
    dbInit();
    printf("Ibetres (1.5.15).\nType \"help\" for help.\n\n");
    interface();
    printf("Disconnected.\n");
    return 0;
}
