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

	// Open File
	FILE *file_ptr = fopen(filename, "r");

	if(file_ptr == NULL){
		fprintf(stderr, "File not found.\n");
		return 0;
	}

	// Seek to the end of the file
  fseek(file_ptr, 0, SEEK_END);

	// Get the size of the file
  long file_size = ftell(file_ptr);

	// Go back to the beginning of file
  rewind(file_ptr);

	// Allocate memory for the file
	char* input = (char*)malloc(file_size * sizeof(char));

	// Counter for file
	int i = 0;
	char c;

	// Read file into memory character by character
	while((c = fgetc(file_ptr))){
		if(c == EOF)
			break;

		// read char into memory
		input[i] = c;
		i++;
	}

	// We have entire file in memory, so we can close it now
	fclose(file_ptr);

	// Initialize Scratch with a stack size of 256 integers
	// => 1024 bytes => 1kb
	sc_init(256);
	
	// Interprete the file as usual
	sc_interprete(input);
	
	// Free input memory
	free(input);

	return 0;
}
