#include "getop2.h"
#include <stdio.h>

int test_numparse_integer(void) {
	char output[100];
	char input[] = "1354 ABC";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_numparse_float(void) {
	char output[100];
	char input[] = "132.35123 325";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_numparse_exponential_notation(void) {
	char output[100];
	char input[] = "1.34E+3 35";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_varparse(void) {
	char output[100];
	char input[] = "A=3";
	load_buffer(input);
	varparse(output);
	printf("test_varparse %s, %s\n", input, output);
	printf("in dictionary A = %s\n", dictionary_lookup('A'));
	flush_buffer();
}

int test_varparse_multiple(void) {
	char output[100];
	char input[] = "A=3 B=5";
	load_buffer(input);
	varparse(output);
	printf("test_varparse %s, %s\n", input, output);
	printf("in dictionary A = %s, B = %s\n", dictionary_lookup('A'), dictionary_lookup('B'));
	flush_buffer();
}

int test_consume_ws(void) {
	char input[] = "\t A=3\t ";
	load_buffer(input);
        char output[100];
        char *p = &output[0];
        while (1) {
                CONSUME_WS(*p);
		/* while ( (*p = getch()) == ' ' || *p == '\t' )
		 *   ;
		 * ungetch(*p)
		 */
		if ( (*p++ = getch()) == EOF) break;
        }
        printf("stripped of white space '%s'\n", output);
	flush_buffer();
}

int main(void) {
	test_numparse_integer();
	test_numparse_float();
	test_numparse_exponential_notation();
	test_varparse();
	test_varparse_multiple();
	/*test_consume_ws();*/
}
