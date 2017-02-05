#include <stdio.h>
#include <stdlib.h>

// TODO: This won't compile on linux
//  or windows as it is. Would need to
//  need to include editline/history.h
//  on linux, and replancement functions
//  for windows for add_history and readline
//  This should be done in IFDEF blocks this 
#include <editline/readline.h>

#include "core/scratch.h"

int main(int argc, char** argv){
	// Initialize with a stack size of 256 integers
	// => 1024 bytes => 1kb
	sc_init(256);

	printf("CScratch 0.0.0.1\n");
	printf("Press Ctrl+C to exit\n\n");

	while(1){
		// Readline, Allocate memory & store input string
		char* input = readline("cscratch> ");

		// Add input to history
		add_history(input);
		
		// Interprete the input using Scratch
		sc_interprete(input);
		
		// Free input memory
		free(input);
	}

	return 0;
}