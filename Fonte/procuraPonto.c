#include "buffend.h"


int procuraPonto(char *Doub) {

	int i;

	for(i = 0; Doub[i] != '\0' && Doub[i] != '.'; i++);

	return i;	

}
