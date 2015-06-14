#include "buffend.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *toUppercase(char *str) {
	int i;
	if (strlen(str) == 0) return str;

	for (i = 0; i < strlen(str); i++) {
		if (islower(str[i])) {
			str[i] = toupper(str[i]);
		}
	}

	return str;
}