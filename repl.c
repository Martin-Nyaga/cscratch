#include <stdio.h>
#include <stdlib.h>

// TODO: Won't compile on Linux, 
//  need to include editline/history.h
//  on linux, and replancement functions
//  for windows for add_history and readline
#include <editline/readline.h>

#include "stack.h"
#include "scratch.h"

// Program Stack
#define PROG_STACK_SIZE 2048
static Stack PROG_STACK;

int main(int argc, char** argv){
	// Initialize the program stack
	stack_init(&PROG_STACK, PROG_STACK_SIZE);

	printf("CScratch 0.0.0.1\n");
	printf("Press Ctrl+C to exit\n\n");

	while(1){
		// Readline, Allocate memory & store input string
		char* input = readline("cscratch> ");

		// Add input to history
		add_history(input);
		
		// Interprete the input using Scratch
		sc_interprete(&PROG_STACK, input);
		
		// Free input memory
		free(input);
	}

	return 0;
}