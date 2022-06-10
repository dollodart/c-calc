#define STACKH 100

struct TOKEN {
	char * tokstr;
	int toktype;
};

int syautomaton(struct TOKEN * tok);
int syparse(char * s);
struct TOKEN * popprint(void);
int clear(void);
