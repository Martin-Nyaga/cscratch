#ifndef _SC_
#define _SC_

void sc_interprete(Stack*, char*);
void sc_call_func(Stack*, char*);
void sc_print_top(Stack*);
void sc_dup_top(Stack*);
void sc_swap(Stack*);
void sc_drop(Stack*);
void sc_drop_stack(Stack*);

// Helper functions
int string_is_number(char*);
void clear_char_buffer(char*, int);

#endif
