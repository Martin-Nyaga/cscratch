
default: src/repl.c src/core/stack.c src/core/hashmap.c src/core/scratch.c src/core/std/scstdlib.c
	cc -std=c99 -Wall src/core/stack.c src/core/hashmap.c src/core/scratch.c src/core/std/scstdlib.c  src/repl.c -ledit -o repl