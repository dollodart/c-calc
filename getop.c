#include <stdio.h>
#include <ctype.h>
#include "calc.h"
#define RECUR 100

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.') {
		if (c == '$') {
			c = getch(); /* 0--9 */
			s[0] = '$';
			s[1] = c;
			s[2] = '\0';
			return VARIABLE;
		}
		return c;
	}
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
