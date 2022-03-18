#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getop2.h"

static char dictionary[NUM_ALPH][DICTIONARY_STR_SIZE];

char * dictionary_lookup(char x) {
	return dictionary[x - ALPHA];
}

/* emulating getch and ungetch for test input */
static int sp = 0;
static char input_buffer[INPUT_BUFFER_SIZE];

int load_buffer(char * s) {
	strcpy(input_buffer, s);
	sp = 0;
}

int flush_buffer() {
	memset(input_buffer, 0, INPUT_BUFFER_SIZE);
	sp = 0;
}

int getch() {
	if (sp >= INPUT_BUFFER_SIZE - 1) {
		printf("at or above capacity, nothing to get\n");
		return EOF;
	}
	return input_buffer[sp++];
}

char ungetch(char c) {
	/* input using char is for compatibility with ungetch implementation for stdin */
	if (sp <= 0) {
		printf("at input start, fill buffer\n");
		return EOF;
	}
	return input_buffer[sp--];
}

int numparse(char s[]) {
	int i, c;

	i = 0; 

	while (isdigit(s[i++] = c = getch())) /* note postfix++ */
		;

        if (c == DECIMAL_DELIM) /* decimal point specification */
                while (isdigit(s[i++] = c = getch()))
			;
        if (c == EXPONENT_SYMBOL_LOWER || c == EXPONENT_SYMBOL_UPPER) /* scientific notation */
        {
                s[i++] = c = getch(); /* optional plus or minus */
                while (isdigit(s[i++] = c = getch())); /* assumed integral exponent */
        }
	ungetch(c);
	s[--i] = '\0';
}

int varparse(char s[]){
	int c, v;
	v = getch(); /* assume no extraneous white space (or can iterate for it) */
	if (ALPHA <= v && v <= ZETA) /* variable */
	{
	    c = getch(); 
	    if (c == EQUALITY_OPERAND) { /* definition */
		numparse(s); /* a number must follow, perhaps with some white space */
		strcpy(dictionary[v - ALPHA], s); /* copy to the allocated dictionary */
		/* set output first character to null */
		s[0] = '\0';
		return RECUR; /* this flag tells getop to recursively call to find the next operand, since this was just a definition */
		}
	    else { /* application/substitution */
		ungetch(c);
		strcpy(s, dictionary[v - ALPHA]);
		return VARIABLE;
	    }
	}
	else { /* function or operand */
		int i = 0;
		s[i] = v;
		while (isalpha(s[++i] = c = getch()))
			;
		if (c != EOF) ungetch(c);
		if (i > 1) return FUNCTION;
		else return s[0]; /* operand */
		}
}

int getop2(char s[]) {

	int c, rflag;

	/* this is "peeking", and one may write a function to peek rather than
	 * pop and push the standard input. */

	c = getch();

	/* if var type, call varparse */
	if (c == ' ' || c == '\t')
		getop2(s);
	else if (!isdigit(c) && c != DECIMAL_DELIM){
		ungetch(c);
		rflag = varparse(s);
		if (rflag == RECUR) {getop2(s);}
		else return rflag;
	}
	else {
		ungetch(c);
		numparse(s);
		return NUMBER;
	}
}
