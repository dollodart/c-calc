#include <stdio.h>
#include "sya.h"

int test_infix(char *test_string) {
    fprintf(stderr, "%s infix ->\n", test_string);
    syparse(test_string); /* this fills printstack, which is accessed with popprint. */
    char c;

    while (c = popprint()) {
	    fprintf(stderr, "entered loop\n");
	    fprintf(stdout, "%c ", c);
    }
    clear(); /* this shouldn't be necessary */
    fprintf(stdout, "\n"); /* this separates tests output in the stdout*/
}


int main(void) {
	test_infix("A*B+C");
	test_infix("A+B*C");
	test_infix("A*(B+C)");
	test_infix("A-B+C");
	test_infix("A*B^C+D");
	test_infix("A*(B+C*D)+E");
}
