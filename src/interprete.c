#include <stdio.h>
#include <stdlib.h>
#include "core/scratch.h"

int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "You must supply a file to interprete.\n");
		return 0;
	}

	// Get filename
	char* filename = argv[1];

	// Load file contents into string
	char* input = sc_load_file(filename);

	// If load file fails
	if(input == NULL){
		return 0;
	}

	// Initialize Scratch with a stack size
	// of 1024 integers
	sc_init(1024);
	
	// Interprete the file as usual
	sc_interprete(input);
	
	// Free input memory
	free(input);

	return 0;
}
