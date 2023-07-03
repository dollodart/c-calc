#include <stdio.h>
#include "sya.h"

int main(void) {
        char input[100];
        char * p = input;
        while ((*p++ = getchar()) != EOF)
                ;
	syparse(input);

	struct TOKEN * t;

	char *s[100];
	int i = 0;
	while (t = popprint()) {
	    s[i++] = t->tokstr;
	}
	while (i >= 0) {
		fprintf(stdout, "%s ", s[i--]);
	}
}
