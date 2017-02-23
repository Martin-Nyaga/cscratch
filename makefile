CC=gcc
CFLAGS=-std=c99 -Wall

all: repl interprete
	
repl: src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/std/string/scstring.c src/core/scratch.c
	$(CC) $(CFLAGS) src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/std/string/scstring.c src/core/scratch.c src/repl.c -ledit -o bin/cscrepl

interprete: src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/std/string/scstring.c src/core/scratch.c
	$(CC) $(CFLAGS) src/core/stack.c src/core/hashmap.c src/core/std/scstdlib.c src/core/std/string/scstring.c src/core/scratch.c src/interprete.c -ledit -o bin/cscinterprete

clean:
	rm bin/cscrepl bin/cscinterprete /usr/local/bin/cscrepl /usr/local/bin/cscinterprete
	rm -rf /usr/local/share/csc
	
test:
	cscinterprete tests/tests.csc

install:
	cp bin/cscrepl /usr/local/bin/cscrepl
	cp bin/cscinterprete /usr/local/bin/cscinterprete
	mkdir /usr/local/share/csc
	mkdir /usr/local/share/csc/lib
	cp -R src/core/std/csc /usr/local/share/csc/lib