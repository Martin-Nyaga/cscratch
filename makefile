default: repl.c stack.c scratch.c
	cc -std=c99 -Wall stack.c scratch.c repl.c -ledit -o repl