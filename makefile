default: src/repl.c src/core/stack.c src/core/scratch.c
	cc -std=c99 -Wall src/core/stack.c src/core/scratch.c src/repl.c -ledit -o repl