#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#define MAXOP 100

/* lookup unary function, then evaluate.
* functions are multiline strings and require
* nested case switching (or do strcmp from
* string.h) */


double ufunclu(char s[]) {
	switch (s[0]) {
		case 'a':
			switch (s[1]) {
				case 's': return asin(pop());
				case 'c': return acos(pop());
				case 't': return atan(pop()); 
			}
		case 'c':
			switch (s[3]) {
				case 'h': return cosh(pop());
				case 'l': return ceil(pop());
				default: return cos(pop());
			}
		case 'e':
			return exp(pop());
		case 'f':
			switch (s[1]) {
				case 'a': return fabs(pop());
				case 'l': return floor(pop());
			}
		case 'l':
			switch (s[3]) {
				case '1': return log10(pop());
				default: return log(pop());
			}
		case 's':
			switch (s[3]) {
				case 'h': return sinh(pop());
				case 't': return sqrt(pop());
				default: return sin(pop());
			}
		case 't':
			switch (s[3]) {
				case 'h': return tanh(pop());
				default: return tan(pop());
			}
	}
}

int main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case FUNCTION:
				push(ufunclu(s));
				break;
			case VARIABLE:
				push(atof(s)); /* the variable must already be substituted by the getop routine */
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-': /* use tilde for negative numbers?
				     otherwise need to know size of operand stack versus size of operator stack */
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push( (int)pop() % (int)op2);
				else
					printf("error: zero modulus\n");
				break;
			case '\n':
				printf("\%.8g\n", pop());
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}
