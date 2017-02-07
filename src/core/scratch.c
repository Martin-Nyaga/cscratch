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

// Max length for a procedure. Can allow fairly long
// Procs: 256 chars
#define MAX_PROC_LENGTH 256

// Error when parsing a proc
#define PROC_ERROR 8989


void sc_init(int stack_size){
	// Initialize the program stack
	sc_stack_init(&PROG_STACK, stack_size);

	// Initialize the function table
	sc_hashmap_init(&FUNCTION_TABLE, 100);

	// Initialize variable table
	sc_hashmap_init(&VARIABLE_TABLE, 100);

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

	// TO mark when a word is ready to be processed
	int word_complete = 0;

	// Read Char by char and build up words
	// up to space or null terminator
	for(i = 0; i <= length; i++){
		if(input[i] == '(' || input[i] == ')'){
			// ignore parens, and leave them as a 
			// formatting choice
		} else if(input[i] == ' ' || input[i] == '\0'){
			// terminate the string
			word_complete = 1;
		} else if(input[i] == '{'){
			// Process proc
			i = sc_process_proc(stack_ptr, input, i);

			// If error return
			if(i == PROC_ERROR){
				free(word_buffer);
				return;
			}
		} else if(input[i] == '/') {
			// Variable declaration
			// Skip forward slash character
			i++;

			// Name buffer of max word length
			char* var_name_buffer = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
			int vc = 0;

			// Collect chars up to space or null terminator
			while(input[i] != ' ' && input[i] != '\0'){
				var_name_buffer[vc] = input[i];
				i++;
				vc++;
			}

			// If valid name, store variable
			if(strlen(var_name_buffer)){
				unsigned int value = sc_stack_pop(stack_ptr);
				
				// Cast value to string
				char* value_as_string = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
				sprintf(value_as_string, "%d", value);

				// Make variable name all caps
				string_to_upper(var_name_buffer);

				// Store value in variable table
				sc_hashmap_store(&VARIABLE_TABLE, var_name_buffer, value_as_string);
			}
		} else {
			// We have a normal character so just add it to the word_buffer
			word_complete = 0;
			word_buffer[wc] = input[i];
			wc++;
		}

		// Overflow error if a single word is longer than the buffer
		if(wc > MAX_WORD_LENGTH){
			fprintf(stderr, "Overflow error, word longer than MAX_WORD_LENGTH!\n");
			free(word_buffer);
			return;
		}

		// Call the function associated with a word
		// if a word was validly collected 
		if(word_complete && strlen(word_buffer)){
			sc_call_func(stack_ptr, word_buffer);

			// Clear buffer again
			clear_char_buffer(word_buffer, MAX_WORD_LENGTH);
			wc = 0;
			word_complete = 0;
		}
	}

	// Free word buffer after interpretation round
	free(word_buffer);
}

// Process a proc, take the input string
// and the current index;
int sc_process_proc(ScStack* stack_ptr, char* input, int i){
	// Procedures, defined by curly braces: {}
	// Skip curly brace char
	i++;
	
	// Get modifier for loops & if statements
	// Loop modifier ':'
	// If statement modifier '?'
	char modifier = input[i];
	if(modifier == ':' || modifier == '?'){
		// If valid modifier, start proc from next char
		i++;
	}

	// Allocate and ready proc buffer
	char* proc_buffer = (char*) malloc(MAX_PROC_LENGTH * sizeof(char));
	clear_char_buffer(proc_buffer, MAX_PROC_LENGTH);
	int pc = 0;

	// Use while to hijack processing
	// Loop up to the closing } storing the string.
	// In the proc buffer
	// Store number of open parens
	int num_open_parens = 1;
	while(num_open_parens){
		// Syntax error if input ends before close proc
		if(input[i] == '\0'){
			fprintf(stderr, "Syntax error. Expected '}' before end of line.!\n");
			free(proc_buffer);
			return PROC_ERROR;
		} else if(input[i] == '}' && num_open_parens == 1){
			// If we are on the closing paren
			// Don't add it to the buffer
			num_open_parens--;
		} else {
			// Increment open parens
			if(input[i] == '{'){
				num_open_parens++;
			}

			// Decrement open parens
			if(input[i] == '}'){
				num_open_parens--;
			}

			proc_buffer[pc] = input[i];
			pc++;
			i++;
		}

		if(pc > MAX_PROC_LENGTH){
			fprintf(stderr, "Overflow error, proc longer than MAX_PROC_LENGTH!\n");
			free(proc_buffer);
			return PROC_ERROR;
		}
	}

	// If a proc has successfully been collected
	if(strlen(proc_buffer)){
		// Loops
		if(modifier == ':'){
			int iterations = sc_stack_pop(stack_ptr);
			int c;

			for(c = 0; c < iterations; c++){
				// Interprete the proc
				sc_interprete(proc_buffer);
			}

			// Conditionals
		} else if(modifier == '?'){
			int condition = sc_stack_pop(stack_ptr);
			if(condition){
				sc_interprete(proc_buffer);
			}
		} else {
			// interprete the proc as usual
			sc_interprete(proc_buffer);
		}

		// Skip the } character finally
		i++;
	}

	// Return the new index
	return i;
}

// Call a function given by a specific string
void sc_call_func(ScStack* stack_ptr, char* word){
	// Make word uppercase
	string_to_upper(word);

	// Check if string is number to add it to the stack
	if(string_is_number(word)){
		sc_stack_push(stack_ptr, (unsigned int) atoi(word));
	} else {
		// Lookup the function in the function table
		NodeH* func_node = sc_hashmap_lookup(&FUNCTION_TABLE, word, HIDE_LOOKUP_ERRORS);

		// If the function is not found
		if(func_node == NULL){
			// Look up the word in the variable table
			NodeH* var_node = sc_hashmap_lookup(&VARIABLE_TABLE, word, HIDE_LOOKUP_ERRORS);

			if(var_node == NULL) {
				// Unknown word
				fprintf(stderr, "Unknown word: '%s'!\n", word);
			} else {
				// Fetch the value from node
				char* value = var_node->value;

				// Cast to uint and push to stack
				sc_stack_push(stack_ptr, (unsigned int) atoi(value));
			}

		} else {
			// Cast the function address into a function pointer
			void (*func_to_call)() = (void (*)()) func_node->value;
			// Call the function with stack as argument
			(*func_to_call)(stack_ptr);
		}
	}
}

// Define a function in the function table given its name & function address
void sc_define_function(char* func_name, void (*func_ptr)()){
	// Cast function address into string
	char* func_address = (char*) func_ptr;

	// Store address in function table
	sc_hashmap_store(&FUNCTION_TABLE, func_name, func_address);
}

// Require a certain number of arguments on the stack
// Useful in STDLIB
int sc_require_arity(ScStack* stack_ptr, int args_num){
	if((stack_ptr->top + 1) < args_num){
		fprintf(stderr, "Requires at least %d items on the stack!\n", args_num);
		return 0;
	} else {
		return 1;
	}
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