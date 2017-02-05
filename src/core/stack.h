#ifndef _SC_STACK_
#define _SC_STACK_

typedef struct ScStack {
	int top;
	unsigned int* contents;
	int max_size;
} ScStack;

void sc_stack_init(ScStack*, int);
int sc_stack_is_empty(ScStack*);
int sc_stack_is_full(ScStack*);
void sc_stack_push(ScStack*, unsigned int);
unsigned int sc_stack_pop(ScStack*);

#endif
