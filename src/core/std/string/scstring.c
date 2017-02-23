#include "scstring.h"

// Decode a string from the stack
// Users are responsible for calling free
char* sc_get_string(ScStack* stack_ptr){
	// Get the string length
	int length = sc_stack_pop(stack_ptr);
	int alloc_size = length + 1;	

	// Allocate memory for the string
	// add 1 for null terminator
	char* str = (char*) malloc(alloc_size * sizeof(char));
	clear_char_buffer(str, alloc_size);
	int i = length;
	char c;

	// Terminate string
	str[i] = '\0';
	i--;

	// Read the string char by char
	while(i >= 0){
		c = sc_stack_pop(stack_ptr);
		str[i] = c;
		i--;
	}

	// Return the string
	return str;
}

// Load a string onto the stack
void sc_put_string(ScStack* stack_ptr, char* str){
	// To hold number version of character
	int c;
	
	// Counter
	int i;

	// To hold the length of the string;
	int len = strlen(str);

	for(i = 0; i < len; i++){
		// Push char to stack
		c = str[i];
		sc_stack_push(stack_ptr, c);
	}

	// Put the length of the string as the last char of
	// The string
	sc_stack_push(stack_ptr, len);
}