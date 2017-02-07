#ifndef _SC_STD_
#define _SC_STD_

#include "../stack.h"
#include "../hashmap.h"
#include "../scratch.h"

// Load Standard Library
void sc_load_std_lib();

// Stack Manipulation
void sc_print_top(ScStack*);
void sc_dup_top(ScStack*);
void sc_swap(ScStack*);
void sc_drop(ScStack*);
void sc_drop_stack(ScStack*);
void sc_print_stack(ScStack*);
void sc_over(ScStack*);
void sc_rotate(ScStack*);

// Simple math
void sc_add(ScStack*);
void sc_subtract(ScStack*);
void sc_multiply(ScStack*);
void sc_divide(ScStack*);
void sc_sqrt(ScStack*);

// Quit
void sc_quit(ScStack*);
void sc_print_words(ScStack*);
#endif