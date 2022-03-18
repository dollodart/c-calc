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

#define STACKH 100
#define INPUT_BUFFER_SIZE 100
#define DICTIONARY_STR_SIZE 12
#define NUM_ALPH 26
#define ALPHA 'A'
#define ZETA 'Z'
#define EQUALITY_OPERAND '='
#define DECIMAL_DELIM '.'
#define EXPONENT_SYMBOL_UPPER 'E'
#define EXPONENT_SYMBOL_LOWER 'e'

#define NUMBER 2
#define OPERATOR 3
#define FUNCTION 4
#define VARIABLE 5
#define RECUR 6
