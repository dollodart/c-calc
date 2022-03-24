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
#define ADD_OPERATOR '+'
#define SUB_OPERATOR '-'
#define MUL_OPERATOR '*'
#define DIV_OPERATOR '/'
#define POW_OPERATOR '^'
#define LEFT_PARANTHESIS '('
#define RIGHT_PARANTHESIS ')'

void push(double);
double pop(void);
double getcache(char []);
int getop(char []);
int getch(void);
char ungetch(int);
