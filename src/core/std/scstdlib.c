#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "../stack.h"
#include "../hashmap.h"
#include "../scratch.h"
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
	sc_define_function("LT", &sc_lt);
	sc_define_function("GT", &sc_gt);

	// system functions
	sc_define_function(">", &sc_get_num_from_bottom);
	sc_define_function("<", &sc_get_num_from_top);
	sc_define_function("EXIT", &sc_quit);
	sc_define_function("PWORDS", &sc_print_words);
	sc_define_function("PVARS", &sc_print_vars);
}

// Print value at top of the stack & pop
void sc_print_top(ScStack* stack_ptr){
	// Require 1 item on stack on stack
	if(!sc_require_arity(stack_ptr, 1)){
		return;
	}

	// Value at top of the stack
	unsigned int top = sc_stack_pop(stack_ptr);
	printf("%d\n", top);
} 

// Duplicate the top item in the stack
void sc_dup_top(ScStack* stack_ptr){
	// Require 1 item on stack on stack
	if(!sc_require_arity(stack_ptr, 1)){
		return;
	}

	// Get top element in the stack & push it again
	// Onto the stack
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	sc_stack_push(stack_ptr, top);
}

// Swap top 2 items on stack
void sc_swap(ScStack* stack_ptr){
	// Require 2 item on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	// Pick top & second and swap them
	unsigned int top = stack_ptr->contents[stack_ptr->top];
	unsigned int second = stack_ptr->contents[stack_ptr->top - 1];

	stack_ptr->contents[stack_ptr->top] = second;
	stack_ptr->contents[stack_ptr->top - 1] = top;
}

// Drop top item from stack
void sc_drop(ScStack* stack_ptr){
	// Require 1 item on stack on stack
	if(!sc_require_arity(stack_ptr, 1)){
		return;
	};

	stack_ptr->top = stack_ptr->top - 1;
}

// Clean stack
void sc_drop_stack(ScStack* stack_ptr){
	while(!sc_stack_is_empty(stack_ptr)){
		sc_stack_pop(stack_ptr);
	}
}

// Print the stack
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

void sc_add(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a + b;
	sc_stack_push(stack_ptr, sum);
}

void sc_subtract(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a - b;
	sc_stack_push(stack_ptr, sum);
}

void sc_multiply(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a * b;
	sc_stack_push(stack_ptr, sum);
}

void sc_divide(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a / b;
	sc_stack_push(stack_ptr, sum);
}

void sc_modulus(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	unsigned int sum = a % b;
	sc_stack_push(stack_ptr, sum);
}

void sc_sqrt(ScStack* stack_ptr){
	// Require 1 items on stack on stack
	if(!sc_require_arity(stack_ptr, 1)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int s = sqrt(a);
	sc_stack_push(stack_ptr, s);
}

void sc_quit(ScStack* _){
	printf("Goodbye!\n");
	exit(0);
}

void sc_over(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	// Stack = 1 2
	// a = 2, b = 1
	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);

	// 1 2 1
	sc_stack_push(stack_ptr, b);
	sc_stack_push(stack_ptr, a);
	sc_stack_push(stack_ptr, b);
}

// Bring 3rd element to top
void sc_rotate(ScStack* stack_ptr){
	// Require 3 items on stack on stack
	if(!sc_require_arity(stack_ptr, 3)){
		return;
	}

	// stack 1 2 3
	// a = 3, b = 2, c = 1
	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
	unsigned int c = sc_stack_pop(stack_ptr);

	// 2 3 1
	sc_stack_push(stack_ptr, b);
	sc_stack_push(stack_ptr, a);
	sc_stack_push(stack_ptr, c);
}

// Print all functions in the function table
void sc_print_words(ScStack* _){
	sc_print_hash(&FUNCTION_TABLE, POINTER_VALUE_FORMAT);
}

// Print all functions in the function table
void sc_print_vars(ScStack* _){
	sc_print_hash(&VARIABLE_TABLE, NORMAL_FORMAT);
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

// Greater than
void sc_gt(ScStack* stack_ptr){
	// Require 2 items on stack on stack
	if(!sc_require_arity(stack_ptr, 2)){
		return;
	}

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
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

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
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

	unsigned int a = sc_stack_pop(stack_ptr);
	unsigned int b = sc_stack_pop(stack_ptr);
	if(a == b){
		sc_stack_push(stack_ptr, 1);
	} else {
		sc_stack_push(stack_ptr, 0);
	}
}

// Get the number specified by an index from the bottom of
// the stack and put a copy on the top of the stack
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