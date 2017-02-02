#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "scratch.h"

// Take a stack, and an input & Interprete the result
void sc_interprete(Stack* stack_ptr, char* input){
	// TODO: Need to read input word by word

	if(string_is_number(input)){
		// TODO: Need to handle the case of integer
		// 	overflow. Right now this can only accept
		//  int digits. Also, what about Negative numbers?
		//  Propose to not support them.

		// FIXME: If blank is entered, it adds a 0 to the stack
		stack_push(stack_ptr, (unsigned int) atoi(input));
		return;
	} 
	
	// FIXME: This is suboptimal. Perhaps use a hash table
	//  to store valid strings and function ptrs, then
	//  lookup the input and call the function defined by the
	//  function ptr?
	//  Leave it like this for the basics, but i'll implement the
	//  hashtable myself.
	if(strcasecmp(input, "PSTACK") == 0){
		stack_print(stack_ptr);
		return;
	}
	
	if(strcasecmp(input, "PRINT") == 0){
		sc_print_top(stack_ptr);
		return;
	}
}

int string_is_number(char* str){
	int len = strlen(str);
	int i;

	for(i = 0; i < len; i++){
		if(!isdigit(str[i])){
			return 0;
		}
	}

	return 1;
}

// Print value at top of the stack & pop
// Show that stack is empty if stack is
// empty
void sc_print_top(Stack* stack_ptr){
	if(stack_is_empty(stack_ptr)){
		printf("Stack is empty.\n");
		return;
	}

	// Value at top of the stack
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	
	// Print thr top item in the stack
	printf("%d\n", top);
	
	// Pop top item from srack
	stack_pop(stack_ptr);
} 