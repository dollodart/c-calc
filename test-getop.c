#include "calc.h"
#include "getop.h"
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

int test_varparse_defn(void) {
	char output[100];
	char input[] = "A=3.53123e+03";
	load_buffer(input);
	varparse(output);
	printf("test_varparse_defn '%s' -> '%s'\n", input, output);
	printf("in dictionary A = '%s'\n", dictionary_lookup('A'));
	flush_buffer();
}

int test_varparse_multiple_defn(void) {
	char output[100];
	char input[] = "A=3 B=5";
	load_buffer(input);
	varparse(output);
	printf("test_varparse_multiple_defn '%s' -> '%s'\n", input, output);
	getch(); /* remove the space delimiting */
	varparse(output);
	printf("test_varparse_multiple_defn (2nd call) '%s' -> '%s'\n", input, output);
	printf("in dictionary A = '%s', B = '%s'\n", dictionary_lookup('A'), dictionary_lookup('B'));
	flush_buffer();
}

int test_varparse_defn_sub(void) {
	char output[100];
	char input[] = "A=3 A";
	load_buffer(input);
	varparse(output);
	printf("test_varparse_defn_sub defn '%s' -> '%s'\n", input, output);
	getch();
	varparse(output);
	printf("test varparse_defn_sub sub '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_varparse_unary(void) {
	char output[100];
	char input[] = "sin 32";
	load_buffer(input);
	varparse(output);
	printf("test_varparse_unary '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_varparse_operator(void) {
	char output[100];
	char input[] = "+";
	load_buffer(input);
	varparse(output);
	printf("test_varparse_operator '%s' -> '%s'\n", input, output);
	flush_buffer();
}

int test_getop_multiple_ints(void) {
	int tflag;
	char output[100];
	char input[] = "1352 32 1 65";
	load_buffer(input);
	for (int i = 0; i < 4; i++) {
		tflag = getop(output);
		printf("test_getop_multiple_ints '%s' -> '%s', tflag=%d\n", input, output, tflag);
	}
	flush_buffer();
}

int test_getop_multiple_floats(void){ /* includes exponential notation */
	int tflag;
	char output[100];
	char input[] = "1.32 5.3e2 6.09E-2";
	load_buffer(input);
	for (int i =0; i < 3; i++) {
		tflag = getop(output);
		printf("test_getop_multiple_floats '%s' -> '%s', tflag=%d\n", input, output, tflag);
	}
	flush_buffer();
}

int test_getop_multiple_vars(void) { /* this is recursive since getop should only store definitions, not return operands for them */
	int tflag;
	char output[100];
	char input[] = "A=3 B=4 C=5";
	load_buffer(input);
	tflag = getop(output);
	printf("test_getop_multiple_vars '%s' -> '%s', tflag=%d\n", input, output, tflag);
	printf("in dictionary A = '%s', B = '%s', C = '%s'\n", dictionary_lookup('A'), dictionary_lookup('B'), dictionary_lookup('C'));
	flush_buffer();
}

int test_getop_ints_opers(void) { /* the simplest practical use case */
	int tflag;
	char output[100];
	char input[] = "3 5 + 8 *";
	load_buffer(input);
	for (int i=0; i< 5; i++) {
		tflag = getop(output);
		printf("test_getop_ints_opers '%s' -> '%s', tflag=%d\n", input, output, tflag);
	}
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

	test_varparse_multiple_defn();
	test_varparse_unary();
	test_varparse_operator();
	test_varparse_defn();
	test_varparse_defn_sub();

	test_getop_multiple_ints();
	test_getop_multiple_floats();
	test_getop_multiple_vars();
	test_getop_ints_opers();

	/*test_consume_ws();*/
}
