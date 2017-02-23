# Scratch
Scratch is a simple stack-based programming language. 

You can find a similar ruby implementation
[here](https://github.com/Martin-Nyaga/scratch). 

# Usage

Clone this repo and run `make`. This will compile a REPL and an interpreter into 
`bin/repl` and `bin/interprete` respectively.

**Note:** At the moment, the REPL only compiles on OSx. I'm still working on it,
and I will make it compile on linux as well when I am done with it.

You can then run the REPL by typing `bin/repl`, or run the interpreter on
any text file using `bin/interpete path/to/file.csc`.

# Hello World in cscratch

```

"Hello World!" pstrln

```

## Language Features

Scratch is a stack based language. The language uses a stack to store data
and runs operations on data from the stack.

At any moment you can print the current stack using `pstack`.
All commands are case insensitive.

### Adding items onto the stack

You can add numbers to the stack simply by entering the number and hitting
enter. You can add several numbers seperated by a space. You can also add negative
numbers. At the moment, only integers are supported.

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
| `exit` | Exit the program (or the REPL) |

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

### Simple Math

The scratch standard library has the simple arithmetic operations `add`, `sub`, `mul`, `div` and `sqrt`.
These operate on the top 2 items in the stack (with the exception of `sqrt` which operates on
the top item only).

Each of these commmands removes those items from the stack and places the result at the top of the stack.

There are also some special operators called `mulall` and `sumall` which 'reduce'
the contents of the stack using `mul` or `sub` respectively.

```
cscratch> 2 3 add print
5
cscratch> pstack

cscratch> 2 3 mul
cscratch> pstack
6
# Twenty Divided by five, then take the quotient, plus three #
cscratch> 20 5 div 3 add print
7
```

- Full explanation of basic concepts

- Repl
- Interprete files

- Stack theory

- - Putting nums on the stack
  - basic Commands
    - Reducing stack theory
  - putting strings on the stack
    - String concepts & theory

  - Comments
  - Setting and getting variables
    - Variable scope theory

  - Procs
    - Proc theory
    - Anon
    - Loop
    - If
    - Function definitions

- Full API docs for all builtin funcs
- Docs of standard library