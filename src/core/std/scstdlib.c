#include "scstdlib.h"

void sc_load_std_lib(){
	// Define Core Functions
	// Stack Manipulation
	sc_define_function("PSTACK", &sc_print_stack);
	sc_define_function("PRINT", &sc_print_top);
	sc_define_function("DUP", &sc_dup_top);
	sc_define_function("SWAP", &sc_swap);
	sc_define_function("DROP", &sc_drop);
	sc_define_function("DROPSTACK", &sc_drop_stack);
	sc_define_function("OVER", &sc_over);
	sc_define_function("ROT", &sc_rotate);
	sc_define_function("COUNT", &sc_count_stack);
	sc_define_function("DUMPSTACK", &sc_dump_stack);

	// Simple math
	sc_define_function("ADD", &sc_add);
	sc_define_function("SUMALL", &sc_add_all);
	sc_define_function("SUB", &sc_subtract);
	sc_define_function("MUL", &sc_multiply);
	sc_define_function("MULALL", &sc_multiply_all);
	sc_define_function("DIV", &sc_divide);
	sc_define_function("SQRT", &sc_sqrt);
	sc_define_function("MOD", &sc_modulus);

	// LOGIC
	sc_define_function("EQ", &sc_eq);
	sc_define_function("NEQ", &sc_neq);
	sc_define_function("LT", &sc_lt);
	sc_define_function("LTEQ", &sc_lteq);
	sc_define_function("GT", &sc_gt);
	sc_define_function("GTEQ", &sc_gteq);

	// system functions
	sc_define_function(">", &sc_get_num_from_bottom);
	sc_define_function("<", &sc_get_num_from_top);
	sc_define_function("EXIT", &sc_quit);
	sc_define_function("PWORDS", &sc_print_words);
	sc_define_function("PVARS", &sc_print_vars);
	sc_define_function("PFUNCS", &sc_print_u_def_functions);

	// System functions, take string arguments
	sc_define_function("LOADFILE", &sc_load_file_from_stack);
	sc_define_function("SYSINVOKE", &sc_sys_invoke);

	// SIMPLE STRING Manipulation
	sc_define_function("PSTRLN", &sc_println_string);
	sc_define_function("PSTR", &sc_print_string);
	sc_define_function("PSTR_RED", &sc_print_string_red);
	sc_define_function("PSTR_GRN", &sc_print_string_green);
	sc_define_function("PSTR_YEL", &sc_print_string_yellow);
	sc_define_function("ITOSTR", &sc_int_to_string);

	// Load Standard CSC funcs
	sc_interprete("\"/usr/local/share/csc/lib/csc/stdfuncs.csc\" loadfile");
	sc_interprete("\"/usr/local/share/csc/lib/csc/strings.csc\" loadfile");
	sc_interprete("\"/usr/local/share/csc/lib/csc/math.csc\" loadfile");
}

// REGION: STACK MANIPULATION
	// Print value at top of the stack & pop
	// PRINT
	void sc_print_top(ScStack* stack_ptr){
		// Require 1 item on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}

		// Value at top of the stack
		int top = sc_stack_pop(stack_ptr);
		printf("%d\n", top);
	} 

	// Duplicate the top item in the stack
	// DUP
	void sc_dup_top(ScStack* stack_ptr){
		// Require 1 item on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}

		// Get top element in the stack & push it again
		// Onto the stack
		int top = stack_ptr->contents[stack_ptr->top];
		sc_stack_push(stack_ptr, top);
	}

	// Swap top 2 items on stack
	// SWAP
	void sc_swap(ScStack* stack_ptr){
		// Require 2 item on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		// Pick top & second and swap them
		int top = stack_ptr->contents[stack_ptr->top];
		int second = stack_ptr->contents[stack_ptr->top - 1];

		stack_ptr->contents[stack_ptr->top] = second;
		stack_ptr->contents[stack_ptr->top - 1] = top;
	}

	// Drop top item from stack
	// DROP
	void sc_drop(ScStack* stack_ptr){
		// Require 1 item on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		};

		stack_ptr->top = stack_ptr->top - 1;
	}

	// Clean stack
	// DROPSTACK
	void sc_drop_stack(ScStack* stack_ptr){
		while(!sc_stack_is_empty(stack_ptr)){
			sc_stack_pop(stack_ptr);
		}
	}

	// Print the stack
	// PSTACK
	void sc_print_stack(ScStack* stack_ptr){
		if(sc_stack_is_empty(stack_ptr)){
			printf("Stack is empty.\n");
			return;
		}
		int i;
		for(i = 0; i <= stack_ptr->top; i ++){
			printf("%d; ", *(stack_ptr->contents + i));
		}
		printf("\n");
	}

	// OVER
	void sc_over(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		// Stack = 1 2
		// a = 2, b = 1
		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		// 1 2 1
		sc_stack_push(stack_ptr, b);
		sc_stack_push(stack_ptr, a);
		sc_stack_push(stack_ptr, b);
	}

	// Bring 3rd element to top
	// ROT
	void sc_rotate(ScStack* stack_ptr){
		// Require 3 items on stack on stack
		if(!sc_require_arity(stack_ptr, 3)){
			return;
		}

		// stack 1 2 3
		// a = 3, b = 2, c = 1
		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		int c = sc_stack_pop(stack_ptr);

		// 2 3 1
		sc_stack_push(stack_ptr, b);
		sc_stack_push(stack_ptr, a);
		sc_stack_push(stack_ptr, c);
	}

	// Get the number specified by an index from the bottom of
	// the stack and put a copy on the top of the stack
	// >
	void sc_get_num_from_bottom(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int index = sc_stack_pop(stack_ptr);

		if(index > stack_ptr->top || index < 0){
			fprintf(stderr, "Overflow Error: Index out of range!\n");
		} else {
			sc_stack_push(stack_ptr, stack_ptr->contents[index]);
		}
	}

	// Get the number specified by an index from the top of
	// the stack and put a copy on the top of the stack
	// <
	void sc_get_num_from_top(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int index = sc_stack_pop(stack_ptr);

		if(index > stack_ptr->top || index < 0){
			fprintf(stderr, "Overflow Error: Index out of range!\n");
		} else {
			index = stack_ptr->top - index;
			sc_stack_push(stack_ptr, stack_ptr->contents[index]);
		}
	}

	// Count num items in stack and put that on top of stack
	// COUNTSTACK
	void sc_count_stack(ScStack* stack_ptr){
		int count = stack_ptr->top + 1;
		sc_stack_push(stack_ptr, count);
	}

	// Dump stack to a file called stack.dump in hex format
	// DUMPSTACK
	void sc_dump_stack(ScStack* stack_ptr){
		// Open dump file
		FILE *d_file = fopen("stack.dump", "w");
		if (d_file == NULL) {
				fprintf(stderr, "Error opening file!\n");
				fclose(d_file);
		}

		// Print char by char in hex
		int i;
		for(i = 0; i <= stack_ptr->top; i++){
			fprintf(d_file, "Ox%x ", stack_ptr->contents[i]);
		}

		// close file
		fclose(d_file);
	}
// END REGION

// REGION: SIMPLE MATH
	void sc_add(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		int sum = a + b;
		sc_stack_push(stack_ptr, sum);
	}

	void sc_subtract(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		int sum = a - b;
		sc_stack_push(stack_ptr, sum);
	}

	void sc_multiply(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		int sum = a * b;
		sc_stack_push(stack_ptr, sum);
	}

	void sc_divide(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		int sum = a / b;
		sc_stack_push(stack_ptr, sum);
	}

	void sc_modulus(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);

		int sum = a % b;
		sc_stack_push(stack_ptr, sum);
	}

	void sc_sqrt(ScStack* stack_ptr){
		// Require 1 items on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int s = sqrt(a);
		sc_stack_push(stack_ptr, s);
	}

	void sc_add_all(ScStack* stack_ptr){
		// Require 1 items on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}

		while(stack_ptr->top){
			sc_add(stack_ptr);
		}
	}

	void sc_multiply_all(ScStack* stack_ptr){
		// Require 1 items on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}

		while(stack_ptr->top){
			sc_multiply(stack_ptr);
		}
	}
// END: REGION

// REGION: LOGIC
	// Greater than
	void sc_gt(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a > b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}

	// LEss than
	void sc_lt(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a < b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}

	// Equal to
	void sc_eq(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a == b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}

	// Not equal to
	void sc_neq(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a != b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}

	// Less than or equal to
	// LTEQ
	void sc_lteq(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a <= b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}

	// Greater than or equal to
	// GTEQ
	void sc_gteq(ScStack* stack_ptr){
		// Require 2 items on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		int a = sc_stack_pop(stack_ptr);
		int b = sc_stack_pop(stack_ptr);
		if(a >= b){
			sc_stack_push(stack_ptr, 1);
		} else {
			sc_stack_push(stack_ptr, 0);
		}
	}
// END REGION

// REGION: SYSTEM FUNCTIONS
	void sc_quit(ScStack* _){
		printf("Goodbye!\n");
		exit(0);
	}

	// Print all functions in the function table
	void sc_print_words(ScStack* _){
		sc_print_hash(&FUNCTION_TABLE, POINTER_VALUE_FORMAT);
	}

	// Print all functions in the function table
	void sc_print_vars(ScStack* _){
		sc_print_hash(&VARIABLE_TABLE, NORMAL_FORMAT);
	}

	// Print all user defined functions
	void sc_print_u_def_functions(ScStack* _){
		sc_print_hash(&U_DEF_FUNCTION_TABLE, NORMAL_FORMAT);
	}

	// Load a file from the stack
	void sc_load_file_from_stack(ScStack* stack_ptr){
		// Require 2 item on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		// Get filename from stack
		char* filename = sc_get_string(stack_ptr);

		// Returns null if file not found.
		char* filedata = sc_load_file(filename);
		
		// Run file data
		// if file was successfuly gotten
		if(filedata != NULL){
			sc_interprete(filedata);
		}

		// Free file data
		free(filename);
		free(filedata);
	}

	// Invoke system call
	void sc_sys_invoke(ScStack* stack_ptr){
		// Require 2 item on stack on stack
		if(!sc_require_arity(stack_ptr, 2)){
			return;
		}

		// Get command from stack
		char* command = sc_get_string(stack_ptr);
		system(command);

		// Free command str
		free(command);
	}

// END REGION

// REGION: STRING MANIPULATION
	// Print a string
	// Top num of the stack usually gives the
	// length of the string, and this can help
	// With mallocing
	void sc_print_string(ScStack* stack_ptr){
		// Require 1 items on stack on stack
		if(!sc_require_arity(stack_ptr, 1)){
			return;
		}
		
		char* str = sc_get_string(stack_ptr);

		printf("%s", str);

		// Free String
		free(str);
	}

	// Println -> prints newline after string
	void sc_println_string(ScStack* stack_ptr){
		sc_print_string(stack_ptr);
		printf("\n");
	}

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

	void sc_print_string_color(ScStack* stack_ptr, char* color){
		printf("%s", color);
		sc_print_string(stack_ptr);
		printf("%s", RESET);
	}

	void sc_print_string_red(ScStack* stack_ptr){
		sc_print_string_color(stack_ptr, RED);
	}

	void sc_print_string_green(ScStack* stack_ptr){
		sc_print_string_color(stack_ptr, GRN);
	}

	void sc_print_string_yellow(ScStack* stack_ptr){
		sc_print_string_color(stack_ptr, YEL);
	}

	void sc_int_to_string(ScStack* stack_ptr){
		int i = sc_stack_pop(stack_ptr);
		char* str = (char*) malloc(MAX_WORD_LENGTH * sizeof(char));
		sprintf(str, "%d", i);
		sc_put_string(stack_ptr, str);
		free(str);
	}
// END REGION
