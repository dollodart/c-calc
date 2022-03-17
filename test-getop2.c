#include "getop2.h"
#include <stdio.h>

int test_numparse_integer(void) {
	char output[100];
	char input[] = "1354 ABC";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
}

int test_numparse_float(void) {
	char output[100];
	char input[] = "132.35123 325";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
}

int test_numparse_exponential_notation(void) {
	char output[100];
	char input[] = "1.34E+3 35";
	load_buffer(input);
	numparse(output);
	printf("numparse '%s' -> '%s'\n", input, output);
}

int test_varparse(void) {
	char output[100];
	char input[] = "A=3";
	load_buffer(input);
	varparse(output);
	printf("test_varparse %s, %s\n", input, output);
	printf("in dictionary A = %s\n", dictionary_lookup('A'));
}

int test_varparse_multiple() {
	char output[100];
	char input[] = "A=3 B=5";
	load_buffer(input);
	varparse(output);
	printf("test_varparse %s, %s\n", input, output);
	printf("in dictionary A = %s, B = %s\n", dictionary_lookup('A'), dictionary_lookup('B'));
}

int main(void) {
	test_numparse_integer();
	test_numparse_float();
	test_numparse_exponential_notation();
	test_varparse();
	test_varparse_multiple();
}
