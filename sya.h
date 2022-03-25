#define STACKH 100

struct TOKEN {
	char * tokstr;
	int toktype;
};

struct TOKEN NULL_TOK = {};

int syautomaton(TOKEN * tok);
int syparse(char * s);
char * popprint(void);
int clear(void);

/* compiler should initialize all fields to 0 */
/*
NULL_TOK.tokstr = '\0';
NULL_TOK.toktype = 0;
*/
