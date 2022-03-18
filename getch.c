#include <stdio.h>
#include <string.h>
#include "calc.h"

static int sp = 0;
static char input_buffer[INPUT_BUFFER_SIZE];

int load_buffer(char * s) {
	strcpy(input_buffer, s);
	sp = 0;
}

int flush_buffer() {
	memset(input_buffer, EOF, INPUT_BUFFER_SIZE);
	sp = 0;
}

int getch() {
	if (sp >= INPUT_BUFFER_SIZE - 1) {
		printf("at or above capacity, nothing to get\n");
		return EOF;
	}
	return input_buffer[sp++];
}

char ungetch(int c) {
	/* input using char is for compatibility with ungetch implementation for stdin */
	if (sp <= 0) {
		printf("at input start, fill buffer\n");
		return EOF;
	}
	return input_buffer[sp--];
}
