#ifndef _SC_
#define _SC_

#include "stack.h"
#include "hashmap.h"

void sc_init(int);
void sc_interprete(char*);

void sc_call_func(ScStack*, char*);
void sc_define_function(char*, void (*)());

// Helper functions
int string_is_number(char*);
void string_to_upper(char*);
void clear_char_buffer(char*, int);

// Stack & Function table
ScHashmap FUNCTION_TABLE;
ScStack PROG_STACK;
#endif
