#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"
#include "hashmap.h"
#include "scratch.h"

#include "std/scstdlib.h"

// No individual word is longer than 10 chars,
// which is the longest size of an unsigned int,
// so we can allocate a buffer of 10 chars
#define MAX_WORD_LENGTH 10

void sc_init(int stack_size){
	// Initialize the program stack
	sc_stack_init(&PROG_STACK, stack_size);

	// Initialize the function table
	sc_hashmap_init(&FUNCTION_TABLE, 100);

	// Load standard library into function table
	sc_load_std_lib();
}

// Take a stack, and an input & Interprete the result
void sc_interprete(char* input){
	// Program stack
	ScStack* stack_ptr = &PROG_STACK;

	int length = strlen(input);
	int i, wc = 0;

	// Word buffer of max word length
	char* word_buffer = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
	
	// Clear the word_buffer to remove any pre-existing
	// junk data that may
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
		
		// Call the function associated with a word
		// if a word was validly collected 
		if(strlen(word_buffer))
			sc_call_func(stack_ptr, word_buffer);
		
		// Clear buffer again
		clear_char_buffer(word_buffer, MAX_WORD_LENGTH);
		wc = 0;
	}

	free(word_buffer);
}

// Call a function given by a specific string
void sc_call_func(ScStack* stack_ptr, char* word){
	// Make word uppercase
	string_to_upper(word);

	// Check if string is number to add it to the stack
	if(string_is_number(word)){
		sc_stack_push(stack_ptr, (unsigned int) atoi(word));
		return;
	}

	// Lookup the function in the function table
	NodeH* func_node = sc_hashmap_lookup(&FUNCTION_TABLE, word);

	// If the function is not found
	if(func_node == NULL){
		// Unknown word
		fprintf(stderr, "Unknown word: '%s'!\n", word);
	} else {
		// Cast the function address into a function pointer
		void (*func_to_call)() = (void (*)()) func_node->value;
		// Call the function with stack as argument
		(*func_to_call)(stack_ptr);
	}
}

// Define a function in the function table given its name & function address
void sc_define_function(char* func_name, void (*func_ptr)()){
	// Cast function address into string
	char* func_address = (char*) func_ptr;

	// Store address in function table
	sc_hashmap_store(&FUNCTION_TABLE, func_name, func_address);
}

// Helper Functions
// -------------
void clear_char_buffer(char* buffer, int len){
	int i;

	for(i = 0; i < len; i++){
		buffer[i] = '\0';
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

// Capitalize a string
void string_to_upper(char* str){
	int i = 0;
	while(str[i]){
		str[i] = toupper(str[i]);
		i++;
	}
}