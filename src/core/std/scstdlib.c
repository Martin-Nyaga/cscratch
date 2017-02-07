#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "../stack.h"
#include "../hashmap.h"
#include "../scratch.h"
#include "scstdlib.h"

void sc_load_std_lib(){
	// Define Core Functions
	// Stack Manipulation
	sc_define_function("PSTACK", &sc_print_stack);
	sc_define_function("PRINT", &sc_print_top);
	sc_define_function("DUP", &sc_dup_top);
	sc_define_function("SWAP", &sc_swap);
	sc_define_function("DROP", &sc_drop);
	sc_define_function("DROPSTACK", &sc_drop_stack);
	sc_define_function("OVER", &sc_over);
	sc_define_function("ROT", &sc_rotate);

	// Simple math
	sc_define_function("+", &sc_add);
	sc_define_function("-", &sc_subtract);
	sc_define_function("*", &sc_multiply);
	sc_define_function("/", &sc_divide);
	sc_define_function("SQRT", &sc_sqrt);

	// system functions
	sc_define_function("EXIT", &sc_quit);
	sc_define_function("PWORDS", &sc_print_words);
}

// Print value at top of the stack & pop
// Show that stack is empty if stack is
// empty
void sc_print_top(ScStack* stack_ptr){
	if(sc_stack_is_empty(stack_ptr)){
		printf("Stack is empty.\n");
		return;
	}

	// Value at top of the stack
	unsigned int top = sc_stack_pop(stack_ptr);
	printf("%d\n", top);
} 

// Duplicate the top item in the stack
// TODO: Should Error here when stack is empty
void sc_dup_top(ScStack* stack_ptr){
	if(sc_stack_is_empty(stack_ptr)){
		printf("Stack is empty");
		return;
	}

	// Get top element in the stack & push it again
	// Onto the stack
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	sc_stack_push(stack_ptr, top);
}

void sc_swap(ScStack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack\n");
		return;
	}

	// Pick top & second and swap them
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	unsigned int second = stack_ptr->contents[stack_ptr->top - 1];

	stack_ptr->contents[stack_ptr->top] = second;
	stack_ptr->contents[stack_ptr->top - 1] = top;
}

// TODO: Proper error handling if stack is empty
void sc_drop(ScStack* stack_ptr){
	if(sc_stack_is_empty(stack_ptr)){
		printf("Stack is empty");
		return;
	}

	stack_ptr->top = stack_ptr->top - 1;
}

void sc_drop_stack(ScStack* stack_ptr){
	// Set top to -1, new pushes will overwrite memory
	stack_ptr->top = -1;
}

// Print the stack
void sc_print_stack(ScStack* stack_ptr){
	if(sc_stack_is_empty(stack_ptr)){
		printf("Stack is empty.\n");
		return;
	}
	int i;
	for(i = 0; i <= stack_ptr->top; i ++){
		printf("%d; ", *(stack_ptr->contents + i));
	}
	printf("\n");
}

void sc_add(ScStack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack\n");
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a + b;
	sc_stack_push(stack_ptr, sum);
}

void sc_subtract(ScStack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack\n");
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a - b;
	sc_stack_push(stack_ptr, sum);
}

void sc_multiply(ScStack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack\n");
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a * b;
	sc_stack_push(stack_ptr, sum);
}

void sc_divide(ScStack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack\n");
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a / b;
	sc_stack_push(stack_ptr, sum);
}

void sc_sqrt(ScStack* stack_ptr){
	if(sc_stack_is_empty(stack_ptr)){
		printf("Stack is empty");
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int s = sqrt(a);
	sc_stack_push(stack_ptr, s);
}

void sc_quit(ScStack* _){
	printf("Goodbye!\n");
	exit(0);
}

void sc_over(ScStack* stack_ptr){
	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
	sc_stack_push(stack_ptr, a);
	sc_stack_push(stack_ptr, b);
	sc_stack_push(stack_ptr, a);
}

// Bring 3rd element to top
void sc_rotate(ScStack* stack_ptr){
	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
	unsigned int c = sc_stack_pop(stack_ptr);

	sc_stack_push(stack_ptr, b);
	sc_stack_push(stack_ptr, a);
	sc_stack_push(stack_ptr, c);
}

// Print all functions in the function table
void sc_print_words(ScStack* _){
	sc_print_hash(&FUNCTION_TABLE, POINTER_VALUE_FORMAT);
}