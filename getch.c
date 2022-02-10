#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* Exercise 4-9 asks to implement get and unget for EOF, which is negative 1.
 * why doesn't that work? we aren't using unsigned integers. */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[])
{
	/* naive implementation. maybe use string length to know before pushing
	 * onto the stack whether the whole string will fit. */
	int c;
	while (c = *s++) ungetch(c);
}
