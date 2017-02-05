#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Initialize the stack
void sc_stack_init(ScStack* stack_ptr, int max_size){
	// Allocate new block of memory for the stack
	// Allow stack to only store Unsigned ints.
	// See sc_interprete in scratch.c
	unsigned int* new_contents_ptr = (unsigned int*) malloc(max_size * sizeof(unsigned int));

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
	return stack_ptr->top >= stack_ptr->max_size - 1;
}

// Push a number to the top of the stack
// TODO: Error if stack is full. Right now it
//  just throws away the values if the stack is full
void sc_stack_push(ScStack* stack_ptr, unsigned int value){
	if (!sc_stack_is_full(stack_ptr)){
		stack_ptr->top++;
		stack_ptr->contents[stack_ptr->top] = value;
	} else {
		fprintf(stderr, "Stack is full!");
	}
}

// Pop top of stack off
// Error if stack is empty
unsigned int sc_stack_pop(ScStack* stack_ptr){
	// FIXME: Could there be a better way of
	//  handling errors altogether?
	if(!sc_stack_is_empty(stack_ptr)){
		unsigned int top = stack_ptr->contents[stack_ptr->top];
		
		// Decrement stack_top so that next push will
		// Overwrite memory
		stack_ptr->top--;

		return top;
	} else {
		fprintf(stderr, "Stack is empty!");
		return 0;
	}
}