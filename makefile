CC=gcc
CFLAGS=-std=c99 -Wall

all: ./repl ./interprete
	
repl: src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/scratch.c
	$(CC) $(CFLAGS) src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/scratch.c src/repl.c -ledit -o bin/repl

interprete: src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/scratch.c
	$(CC) $(CFLAGS) src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/scratch.c src/interprete.c -ledit -o bin/interprete

clean:
	rm bin/repl bin/interprete
	