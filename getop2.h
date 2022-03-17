int getop2(char s[]);
int varparse(char s[]);
int numparse(char s[]);
int load_buffer(char s[]);
int flush_buffer();
char * dictionary_lookup(char);
int getch();
char ungetch(char c);

#define CONSUME_WS(c) while ((c = getch()) == ' ' || c == '\t') \
				  ;\
		      ungetch(c);
