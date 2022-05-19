#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#include "getop.h"

static char dictionary[NUM_ALPH][DICTIONARY_STR_SIZE];

char * dictionary_lookup(char x) {
	return dictionary[x - ALPHA];
}

int numparse(char s[]) {
	int i, c;

	i = 0; 

	while (isdigit(s[i++] = c = getch())) /* note postfix++ */
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
	else { /* function or operator */
		int i = 0;
		s[i] = v;
		while (isalpha(s[++i] = c = getch()))
			;
		if (c != EOF) ungetch(c);
		if (i > 1) return FUNCTION;
		s[1] = '\0';
		switch (s[0]) {
			case '+': return ADD_OPERATOR;
			case '-': return SUB_OPERATOR;
			case '*': return MUL_OPERATOR;
			case '/': return DIV_OPERATOR;
			case '^': return POW_OPERATOR;
			case '(': return LEFT_PARANTHESIS;
			case ')': return RIGHT_PARANTHESIS;
			}
		}
}

int getop(char s[]) {

	int c, rflag;

	/* this is "peeking", and one may write a function to peek rather than
	 * pop and push the standard input. */

	c = getch();

	/* if var type, call varparse */
	if (c == ' ' || c == '\t')
		getop(s);
	else if (c == EOF)
		return EOF;
	else if (!isdigit(c) && c != DECIMAL_DELIM){
		ungetch(c);
		rflag = varparse(s);
		if (rflag == RECUR) {getop(s);}
		else return rflag;
	}
	else {
		ungetch(c);
		numparse(s);
		return NUMBER;
	}
}
