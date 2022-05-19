int getop(char s[]);
int varparse(char s[]);
int numparse(char s[]);
int load_buffer(char s[]);
int flush_buffer();
char * dictionary_lookup(char);

#define CONSUME_WS(c) while ((c = getch()) == ' ' || c == '\t') \
				  ;\
		      ungetch(c);
