#include "buffend.h"

void dbInit() {
	if(system("mkdir data") == -1)
		printf("ERROR: It was not possible to initialize the ibtres\n");;
	createDB("ibetres");
}