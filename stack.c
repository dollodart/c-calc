#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
#define CACHE_MAXVAL 10

int sp=0;
double val[MAXVAL];
double cache[CACHE_MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;

		double ival = f;
		double ipval;
		for (int i = 0; i < CACHE_MAXVAL - 1; i++) {
			ipval = cache[i+1];
			cache[i+1] = cache[i];
			cache[i] = ival;
			ival = ipval;
		}
	}
	else printf("error: stack full, can't push %g\n", f);

}
double pop(void){
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void peek(void){
        if (sp > 0)
                printf("top value is %g", val[sp]);
        else {
                printf("error: stack empty\n");
        }
}

void duplicate(void) {
        if (sp > 0)
        {
                double temp = val[sp];
                val[++sp] = temp;
        }
        else {
                printf("error: stack empty\n");
        }
}

void swap(void) {
        if (sp > 0) /* can't test for sp > 1, unless compiler knows where array start is */
        {sp--;
        if (sp > 0) {
             sp++; /* put pointer back at top to use the other routines */
             double temp = pop(); 
             double temp2 = pop();
             push(temp); 
             push(temp2);
        }
        else printf("error: stack empty\n");
        }
        else printf("error: stack empty\n");
}

void clear(void) {
        while (sp--); /* you don't need to fill the memory with zeros, that is, set val[sp] = 0 */
}
