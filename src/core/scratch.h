#ifndef _SC_
#define _SC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"
#include "hashmap.h"

#include "std/scstdlib.h"
#include "std/string/scstring.h"

void sc_init(int);
void sc_interprete(char*);
char* sc_load_file(char*);

int sc_process_proc(ScStack*, char*, int);
int sc_store_variable(ScStack* stack_ptr, char* input, int i);

void sc_call_func(ScStack*, char*);
void sc_define_function(char*, void (*)());
int sc_require_arity(ScStack*, int);

void sc_call_builtin_func(ScStack* stack_ptr, NodeH* func_node);
void sc_get_variable(ScStack* stack_ptr, NodeH* var_node);
void sc_call_u_def_func(NodeH* u_def_func_node);

// Helper functions
int is_special(char);
int string_is_number(char*);
void string_to_upper(char*);
void clear_char_buffer(char*, int);

// Stack & Function table & variable table
ScHashmap FUNCTION_TABLE;
ScStack PROG_STACK;
ScHashmap VARIABLE_TABLE;
ScHashmap U_DEF_FUNCTION_TABLE;

// Max word length
#define MAX_WORD_LENGTH 1024

// Max length for a procedure
#define MAX_PROC_LENGTH 2048

// Error when parsing a proc
#define PROC_ERROR 8989

// Error when storing a variable
#define VARIABLE_ERROR 89898
#endif
