#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Initialize the stack
void sc_stack_init(ScStack* stack_ptr, int max_size){
	// Allocate new block of memory for the stack
	// Allow stack to only store ints.
	// See sc_interprete in scratch.c
	int* new_contents_ptr = (int*) malloc(max_size * sizeof(int));

	// Init stack with Empty Contents
	stack_ptr->contents = new_contents_ptr;
	// Stack is empty
	stack_ptr->top = -1;
	// max_size of stack
	stack_ptr->max_size = max_size;
}

// Check if Stack is empty
int sc_stack_is_empty(ScStack* stack_ptr){
	return stack_ptr->top == -1;
}

// Check if stack is full
int sc_stack_is_full(ScStack* stack_ptr){
	return stack_ptr->top >= (stack_ptr->max_size - 1);
}

// Push a number to the top of the stack
void sc_stack_push(ScStack* stack_ptr, int value){
	if (!sc_stack_is_full(stack_ptr)){
		stack_ptr->top++;
		stack_ptr->contents[stack_ptr->top] = value;

	} else {
		fprintf(stderr, "Stack is full!\n");
	}
}

// Pop top of stack off
// Error if stack is empty
int sc_stack_pop(ScStack* stack_ptr){
	if(!sc_stack_is_empty(stack_ptr)){
		int top = stack_ptr->contents[stack_ptr->top];
		
		// Decrement stack_top so that next push will
		// Overwrite memory
		stack_ptr->top--;

		return top;
	} else {
		fprintf(stderr, "Stack is empty!\n");
		return 0;
	}
}