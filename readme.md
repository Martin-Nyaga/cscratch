# Scratch
Scratch is a simple stack-based programming language.

This implementation of scratch is in C, and is called cscratch. You can
find a ruby implementation [here](https://github.com/Martin-Nyaga/scratch). 

All these are implementations of the language in [this tutorial](http://scratch-lang.notimetoplay.org/),
originally in javascript.

# Usage

Clone this repo. Run `make` to compile the REPL.

**Note:** At the moment, the REPL only compiles on mac. I'm still working on it,
and I will make it compile on linux as well when I am done with it.

You can then  run the REPL by typing `repl`.

## Language Features

Scratch is a stack based language. The language uses a stack to store data
and runs operations on data from the stack.

At any moment you can print the stack using `pstack`.
All commands are case insensitive.

### Adding items onto the stack

You can add numbers to the stack simply by entering the number and hitting
enter. You can add several numbers seperated by a space.

```
cscratch> 1
cscratch> pstack
1
cscratch> 2 3 5 2 90
cscratch> pstack
1 ; 2 ; 3 ; 5 ; 2 ; 90
```

### Stack manipulation

There are several commands to manipulate the stack as shown below:

| Command | Description|
| ------------- |--------|
| `pstack` | Print the stack. |
| `print` | Print the top item in the stack. This drops the item from the stack. |
| `dup` | Duplicate the top item in the stack. |
| `swap` | Swap the top 2 items in the stack. |
| `drop` | Remove the top item in the stack. |
| `dropstack` | Clear the stack. |
| `exit` | Exit the repl |

You can mix and match commands and run them as a single command. Scratch executes one word at a time.

```
cscratch> 19
cscratch> print
19
cscratch> pstack
Stack is empty.
cscratch> 19
cscratch> dup pstack
19 ; 19
cscratch> dropstack
cscratch> pstack
Stack is empty.
cscratch> 19 dup dup drop 12 swap pstack
19 ; 12 ; 19
cscratch> dropstack print
== Error: This command requres at least 1 item on the stack
```

### Coming Soon: Simple Math

The scratch standard library has the simple arithmetic operators `+`, `-`, `*`, `&` and `sqrt`.
These operate on the top 2 items in the stack (with the exception of `sqrt` which operates on
the top item only).

Each of these commmands removes those items from the stack and places the result at the top of the stack.

```
cscratch> 2 3 + print
5
cscratch> pstack

cscratch> 2 3 *
cscratch> pstack
6
# Twenty Divided by five, then take the quotient, plus three #
cscratch> 20 5 / 3 + print
7
```

### More Coming Soon

- Running cscratch scripts
- Comments