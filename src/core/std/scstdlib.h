#ifndef _SC_STD_
#define _SC_STD_

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
void sc_get_num_from_bottom(ScStack*);
void sc_get_num_from_top(ScStack*);
void sc_count_stack(ScStack* stack_ptr);
void sc_dump_stack(ScStack* stack_ptr);

// Simple math
void sc_modulus(ScStack*);
void sc_add(ScStack*);
void sc_subtract(ScStack*);
void sc_multiply(ScStack*);
void sc_divide(ScStack*);
void sc_sqrt(ScStack*);
void sc_add_all(ScStack*);
void sc_multiply_all(ScStack*);

// Simple String Manipulation
// Require string library
void sc_println_string(ScStack* stack_ptr);
void sc_print_string(ScStack* stack_ptr);
void sc_print_string_color(ScStack* stack_ptr, char*);
void sc_print_string_red(ScStack* stack_ptr);
void sc_print_string_green(ScStack* stack_ptr);
void sc_print_string_yellow(ScStack* stack_ptr);
void sc_int_to_string(ScStack* stack_ptr);


// Logic
void sc_gt(ScStack*);
void sc_lt(ScStack*);
void sc_eq(ScStack*);
void sc_lteq(ScStack*);
void sc_gteq(ScStack*);
void sc_neq(ScStack*);

// System
void sc_quit(ScStack*);
void sc_print_words(ScStack*);
void sc_print_vars(ScStack* _);
void sc_print_u_def_functions(ScStack* _);
void sc_load_file_from_stack(ScStack* stack_ptr);
void sc_sys_invoke(ScStack* stack_ptr);

#endif