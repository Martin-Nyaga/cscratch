#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "scratch.h"

// No individual word is longer than 10 chars,
// which is the longest size of an unsigned int,
// so we can allocate a buffer of 10 chars
#define MAX_WORD_LENGTH 10

// Take a stack, and an input & Interprete the result
void sc_interprete(Stack* stack_ptr, char* input){
	// TODO: Need to read input word by word
	int length = strlen(input);
	int i, wc = 0;

	// Word buffer of max word length
	char* word_buffer = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
	
	// Fill the word_buffer with spaces to remove any data that may
	// interfere with interpretation
	clear_char_buffer(word_buffer, MAX_WORD_LENGTH);

	// Read Char by char and build up words
	// up to space or null terminator
	for(i = 0; i < length; i++){
		while(input[i] != ' ' && input[i] != '\0'){
			word_buffer[wc] = input[i];
			i++;
			wc++;

			// Overflow error if a single word is longer than the buffer
			if(wc > MAX_WORD_LENGTH){
				printf("Overflow error, word too long.\n");
				return;
			}
		}
		
		// Manually terminate string
		word_buffer[wc + 1] = '\0';
		
		// Call the function associated with a word
		sc_call_func(stack_ptr, word_buffer);
		
		// Clear buffer again
		clear_char_buffer(word_buffer, MAX_WORD_LENGTH);
		wc = 0;
	}

	free(word_buffer);
}


void sc_call_func(Stack* stack_ptr, char* word){
	if(string_is_number(word)){
		// TODO: Need to handle the case of integer
		// 	overflow. Right now this can only accept
		//  int digits. Also, what about Negative numbers?
		//  Propose to not support them.

		// FIXME: If blank is entered, it adds a 0 to the stack
		stack_push(stack_ptr, (unsigned int) atoi(word));
		return;
	}
	
	// FIXME: This bunch of if's is not very pretty.
	// 	Perhaps use a hashmap
	//  to store valid strings and function ptrs, then
	//  lookup the word and call the function defined by the
	//  function ptr?
	if(strcasecmp(word, "PSTACK") == 0){
		stack_print(stack_ptr);
		return;
	}
	
	if(strcasecmp(word, "PRINT") == 0){
		sc_print_top(stack_ptr);
		return;
	}

	if(strcasecmp(word, "DUP") == 0){
		sc_dup_top(stack_ptr);
		return;
	}

	if(strcasecmp(word, "SWAP") == 0){
		sc_swap(stack_ptr);
		return;
	}

	if(strcasecmp(word, "DROP") == 0){
		sc_drop(stack_ptr);
		return;
	}

	if(strcasecmp(word, "DROPSTACK") == 0){
		sc_drop_stack(stack_ptr);
		return;
	}

	if(strcasecmp(word, "EXIT") == 0){
		printf("Goodbye!\n");
		exit(0);
		return;
	}

	// Unknown word
	printf("Unknown word %s\n", word);
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

// Duplicate the top item in the stack
// TODO: Should Error here when stack is empty
void sc_dup_top(Stack* stack_ptr){
	if(stack_is_empty(stack_ptr)){
		printf("Stack is empty");
		return;
	}

	// Get top element in the stack & push it again
	// Onto the stack
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	stack_push(stack_ptr, top);
}

void sc_swap(Stack* stack_ptr){
	if(stack_ptr->top < 1){
		printf("Requires at least 2 items on the stack");
		return;
	}

	// Pick top & second and swap them
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	unsigned int second = stack_ptr->contents[stack_ptr->top - 1];

	stack_ptr->contents[stack_ptr->top] = second;
	stack_ptr->contents[stack_ptr->top - 1] = top;
}

// TODO: Proper error handling if stack is empty
void sc_drop(Stack* stack_ptr){
	if(stack_is_empty(stack_ptr)){
		printf("Stack is empty");
		return;
	}

	stack_ptr->top = stack_ptr->top - 1;
}

void sc_drop_stack(Stack* stack_ptr){
	// Set top to -1, new pushes will overwrite memory
	stack_ptr->top = -1;
}

void clear_char_buffer(char* buffer, int len){
	int i;

	for(i = 0; i < len; i++){
		buffer[i] = '\0';
	}
}