#define NUMBER '0'
#define FUNCTION '1'
#define VARIABLE '2'
void push(double);
double pop(void);
double getcache(char []);
int getop(char []);
int getch(void);
void ungetch(int);
