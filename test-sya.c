#include <stdio.h>
#include "sya.h"

int test_infix(char *test_string) {
    fprintf(stderr, "%s infix ->\n", test_string);
    syparse(test_string); /* this fills printstack, which is accessed with popprint. */
    char * s;

    while (s = popprint()) {
	    fprintf(stderr, "entered loop\n");
	    fprintf(stdout, "%s ", s);
    }
    clear(); /* this shouldn't be necessary */
    fprintf(stdout, "\n"); /* this separates tests output in the stdout*/
}


int main(void) {
	test_infix("2*3+4");
	test_infix("2*3+4");
	test_infix("2+3*4");
	test_infix("2*(3+4)");
	test_infix("2-3+4");
	test_infix("2*3^4+5");
	test_infix("2*(3+4*5)+6");
}
