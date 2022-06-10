#include <stdio.h>
#include <string.h>
#include "sya.h"
#include "calc.h"
#include "getop.h"

struct TOKEN stack[STACKH];
struct TOKEN printstack[STACKH];
int sp;
int spp;

struct TOKEN NULL_TOK = {};

/* note: reserve the zero index of the array for empty (not necessary, a negative index could be used)
 * for this reason, we need a prefix increment. */
int tpush(struct TOKEN * tok) {
  if (sp < STACKH) stack[++sp] = *tok;
  else fprintf(stderr, "error: stack full, can't print %s\n", tok->tokstr);
  return 0;
}

struct TOKEN * tpop(void) {
  if (sp > 0) return &stack[sp--];
  else fprintf(stderr, "error: stack empty, can't pop\n");
  return &NULL_TOK;
}

int print(struct TOKEN * tok) {
  if (spp < STACKH) printstack[++spp] = *tok;
  else fprintf(stderr, "error: stack full, can't print %s\n", tok->tokstr);
  return 0;
}

struct TOKEN * popprint(void) {
	if (spp > 0) return &printstack[spp--];
	else fprintf(stderr, "error: print stack empty, can't pop\n");
	return 0;
}

int clear_print(void) {while (spp--) ; spp++; printstack[spp] = NULL_TOK;}
int clear_stack(void) {while (sp--) ; sp++; stack[sp] = NULL_TOK;}
int clear(void) {clear_print(); clear_stack();}

int get_prec(int toktype) {
	switch (toktype) {
		case ADD_OPERATOR: case SUB_OPERATOR: return 1; break;
		case MUL_OPERATOR: case DIV_OPERATOR: return 2; break;
		case POW_OPERATOR: return 3; break;
		default: return -1; break;
	}
}

int get_assoc(int toktype) {
	switch (toktype) {
		case POW_OPERATOR: return 1; break;
		default: return 0; break;}
}

/*
 * Summary of the Rules

    1. If the incoming symbols is an operand, print it.

    2. If the incoming symbol is a left parenthesis, print [sic, tpush] it on the stack.

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

int syautomaton(struct TOKEN * tok) {
	struct TOKEN * tok2;
	int prec, prec2, assoc, assoc2;
	fprintf(stderr, "on token '%s'\n  ", tok->tokstr);
	switch (tok->toktype) {
		case SUB_OPERATOR: case ADD_OPERATOR: case DIV_OPERATOR: case MOD_OPERATOR: case MUL_OPERATOR: case POW_OPERATOR:
			/* rule 4 */
			if (sp == 0) {
				fprintf(stderr, "rule 4, empty stack\n");
				tpush(tok); 
				return 0;}
			tok2 = tpop();
			if (tok2->toktype == LEFT_PARANTHESIS) {
				fprintf(stderr, "rule 4, left paranthesis\n");
				tpush(tok2);
				tpush(tok);
				return 0;}
			
			prec = get_prec(tok->toktype);
			assoc = get_assoc(tok->toktype);

			/* rules 5 and 6 */
			while ( (prec2 = get_prec(tok2->toktype)) >= prec
				|| (prec2 == prec && get_assoc(tok2->toktype) == 0) )
			{
				fprintf(stderr, "rule 6, precedence/association delta\n");
				if (sp == 0 &&
				   (get_prec(tok2->toktype) >= prec ||
				    prec2 == prec && get_assoc(tok2->toktype) == 0)) {
					/* revert to rule 4 if we have no more operators in the stack*/
					fprintf(stderr, "rule 4 within rule 6 (empty stack)\n");
			 		print(tok2);
					tpush(tok);
					return 0;
				}
				else {
					print(tok2);
					tok2 = tpop();
				}
			}

			fprintf(stderr, "rule 5 (maybe at end of rule 6), precedence/association delta\n");
			tpush(tok2);
			tpush(tok);

			break;
		case RIGHT_PARANTHESIS: /* rule 3 */
			fprintf(stderr, "rule 3, right paranthesis\n");
			fprintf(stderr, "current value of operator stack is '%s'", stack[sp].tokstr);
			while ((tok2 = tpop())->toktype != LEFT_PARANTHESIS) {
				print(tok2);
			}
			break;
		case LEFT_PARANTHESIS: /* rule 2 */
			fprintf(stderr, "rule 2, left paranthesis\n");
			tpush(tok);
			break;
		default: /* rule 1 */
			fprintf(stderr, "rule 1, operand\n");
			print(tok);
			break;
	}
}


int syparse(char * s) {
    load_buffer(s);
    int toktype;
    char ss[100];
    struct TOKEN * tok;
    int tokc = 0;

    while ((toktype = getop(ss)) > -1) {
	    tok = &stack[tokc++];
	    tok->tokstr = strdup(ss);
	    tok->toktype = toktype;
	    syautomaton(tok);
    }

    while (sp) {
	    tok = tpop();
	    print(tok);
	    fprintf(stderr, "end tpop operator %s, printed to print stack\n", tok->tokstr);
    }
    flush_buffer();
}
