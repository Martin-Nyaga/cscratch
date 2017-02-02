#ifndef _STACK_
#define _STACK_

typedef struct _Stack {
	int top;
	unsigned int* contents;
	int max_size;
} Stack;

void stack_init(Stack*, int);
int stack_is_empty(Stack*);
int stack_is_full(Stack*);
void stack_push(Stack*, unsigned int);
unsigned int stack_pop(Stack*);
void stack_print(Stack*);
void stack_destroy(Stack*);

#endif
