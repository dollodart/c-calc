#include <stdio.h>
#include "sya.h"

char stack[STACKH];
char printstack[STACKH];
int sp;
int spp;

/* note: reserve the zero index of the array for empty (not necessary, a negative index could be used)
 * for this reason, we need a prefix increment. */
int push(char s) {
  if (sp < STACKH) stack[++sp] = s;
  else fprintf(stderr, "error: stack full, can't print %c\n", s);
  return 0;
}

int pop(void) {
  if (sp > 0) return stack[sp--];
  else fprintf(stderr, "error: stack empty, can't pop\n");
  return '\0';
}

int print(char s) {
  if (spp < STACKH) printstack[++spp] = s;
  else fprintf(stderr, "error: stack full, can't print %c\n", s);
  return 0;
}

int popprint(void) {
	if (spp > 0) return printstack[spp--];
	else fprintf(stderr, "error: print stack empty, can't pop\n");
	return 0;
}

int clear_print(void) {printstack[spp] = '\0'; while (spp--) printstack[spp] = '\0'; spp++;}
int clear_stack(void) {stack[sp] = '\0'; while (sp--) stack[sp] = '\0'; sp++;}
int clear(void) {clear_print(); clear_stack();}

int get_prec(char s) {
	switch (s) {
		case '^': return 3; break;
		case '/': case '*': return 2; break;
		case '-': case '+': return 1; break;
		default: return -1; break;
	}
}

int get_assoc(char s) {
	switch (s) {
		case '^': return 1; break;
		default: return 0; break;}
}

/*
 * Summary of the Rules

    1. If the incoming symbols is an operand, print it.

    2. If the incoming symbol is a left parenthesis, print [sic, push] it on the stack.

    3. If the incoming symbol is a right parenthesis: discard the right
    parenthesis, pop and print the stack symbols until you see a left
    parenthesis. Pop the left parenthesis and discard it.

    4. If the incoming symbol is an operator and the stack is empty or contains a
    left parenthesis on top, print the incoming operator onto the stack.

    5. If the incoming symbol is an operator and has either higher precedence than
    the operator on the top of the stack, or has the same precedence as the
    operator on the top of the stack and is right associative -- print it on the
    stack.

    6. If the incoming symbol is an operator and has either lower precedence than
    the operator on the top of the stack, or has the same precedence as the
    operator on the top of the stack and is left associative -- continue to pop
    the stack until this is not true. Then, print the incoming operator.

    7. At the end of the expression, pop and print all operators on the stack. (No
    parentheses should remain.)
*/

int syautomaton(char s) {
	char s2;
	int prec, prec2, assoc, assoc2;
	fprintf(stderr, "on char %c\n  ", s);
	switch (s) {
		case '-': case '+': case '/': case '%': case '*': case '^':
			/* rule 4 */
			if (sp == 0) {
				fprintf(stderr, "rule 4, empty stack\n");
				push(s); 
				return 0;}
			s2 = pop();
			if (s2 == '(') {
				fprintf(stderr, "rule 4, left paranthesis\n");
				push(s2);
				push(s);
				return 0;}
			
			prec = get_prec(s);
			assoc = get_assoc(s);

			/* rules 5 and 6 */
			while ( (prec2 = get_prec(s2)) >= prec
				|| (prec2 == prec && get_assoc(s2) == 0) )
			{
				fprintf(stderr, "rule 6, precedence/association delta\n");
				if (sp == 0 &&
				   (get_prec(s2) >= prec ||
				    prec2 == prec && get_assoc(s2) == 0)) {
					/* revert to rule 4 if we have no more operators in the stack*/
					fprintf(stderr, "rule 4 within rule 6 (empty stack)\n");
			 		print(s2);
					push(s);
					return 0;
				}
				else {
					print(s2);
					s2 = pop();
				}
			}

			fprintf(stderr, "rule 5 (maybe at end of rule 6), precedence/association delta\n");
			push(s2);
			push(s);

			break;
		case ')': /* rule 3 */
			fprintf(stderr, "rule 3, right paranthesis\n");
			fprintf(stderr, "current value of operator stack is %s", stack);
			while ((s2 = pop()) != '(') {
				print(s2);
			}
			break;
		case '(': /* rule 2 */
			fprintf(stderr, "rule 2, left paranthesis\n");
			push(s);
			break;
		default: /* rule 1 */
			fprintf(stderr, "rule 1, operand\n");
			print(s);
			break;
	}
}

int syparse(char * s) {
    char c;
    while (c = *s++) {
	    syautomaton(c);
    }
    while (sp) {
	    c = pop();
	    print(c);
	    fprintf(stderr, "end pop operator %c, printed to print stack\n", c);
    }
}
