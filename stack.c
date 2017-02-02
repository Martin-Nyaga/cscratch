#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Initialize the stack
void stack_init(Stack* stack_ptr, int max_size){
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
int stack_is_empty(Stack* stack_ptr){
	return stack_ptr->top == -1;
}

// Check if stack is full
int stack_is_full(Stack* stack_ptr){
	return stack_ptr->top >= stack_ptr->max_size - 1;
}

// Push a number to the top of the stack
// TODO: Error if stack is full
void stack_push(Stack* stack_ptr, unsigned int value){
	stack_ptr->top++;
	stack_ptr->contents[stack_ptr->top] = value;
}

// Print the stack
void stack_print(Stack* stack_ptr){
	if(stack_is_empty(stack_ptr)){
		printf("Stack is empty.\n");
		return;
	}
	int i;
	for(i = 0; i <= stack_ptr->top; i ++){
		printf("%d; ", *(stack_ptr->contents + i));
	}
	printf("\n");
}

// Pop top of stack off
// Error if stack is empty
unsigned int stack_pop(Stack* stack_ptr){
	// FIXME: Could there be a better way of
	//  handling errors altogether?
	if(!stack_is_empty(stack_ptr)){
		unsigned int top = stack_ptr->contents[stack_ptr->top];
		
		// Decrement stack_top so that next push will
		// Overwrite memory
		stack_ptr->top--;

		return top;
	} else {
		printf("Stack is empty.");
		return 0;
	}
}

void stack_destroy(Stack* stack_ptr){
	// TODO:
}