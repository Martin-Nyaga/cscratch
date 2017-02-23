# Load testing framework #
"/usr/local/share/csc/lib/csc/opt/stdtest.csc" loadfile

# ------- TEST SETUP ------------ #

# Test Format: #
# FUNCTION NAME #
  # Given:G #
  # When:W #
  # Then:T #
    # test name : test.test_ok #
  # Dropstack & other teardown methods #

# Variable to store manual checks #
# Incremented when a test needs visual checking #
0 /test_checks

pln
"Starting test suite..." pstrln

# Function to Print underline #
{$pequals$ 61 60 {: dup } 61 pstrln }
pequals

# ------- END TEST SETUP ---------- #


# ------- STACK MANIPULATION WORDS TESTS ---- #
  pln
  "Stack Manipulation Words" pstrln
  pln

  # PSTACK #
    #G# 1 2
    #W# pstack
        "1, 2" test.check
    #T# 1
        "PRINT: prints the the stack" pstrln
    test_checks inc /test_checks
    dropstack

  # PRINT #
    #G# 1 2
    #W# print
        "2" test.check
    #T# count 1 eq 
        "PRINT: prints the top of the stack (drops)" test.assert
    test_checks inc /test_checks
    dropstack

  # DUP #
    #G# 2
    #W# dup
    #T# count 2 eq
        "DUP: duplicates the top of the stack" test.assert
    dropstack

  # SWAP #
    #G# 3 2
    #W# swap
    #T# 3 eq
        "SWAP: swaps the top two numbers in the stack" test.assert
    dropstack

  # DROP #
    #G# 3 2
    #W# swap
    #T# 3 eq
        "DROP: drops the top number in the stack" test.assert
    dropstack

  # DROPSTACK #
    #G# 3 2
    #W# dropstack
    #T# count 0 eq
        "DROPSTACK: drops the stack" test.assert
    dropstack

  # OVER #
    #G# 3 2
    #W# over
    #T# 3 eq
        "OVER: Copies 2nd element from top to top" test.assert
    dropstack

  # ROT #
    #G# 3 2 1
    #W# rot
    #T# 3 eq
        "ROT: Performs the rotate operation: a, b, c ->  b, c, a" test.assert
    dropstack

  # COUNT #
    #G# 3 2 1
    #W# count
    #T# 3 eq
        "COUNT: Gives correct count of elements" test.assert
    dropstack

  # DUMPSTACK #
    #G# 1
    #W# dumpstack
    #T# "cat stack.dump" sysinvoke pln
        "Ox1" test.check
        "DUMPSTACK: Dumps the stack to a file" pstrln
    "rm stack.dump" sysinvoke
    test_checks inc /test_checks
    dropstack

# ------- END STACK MANIPULATION WORDS TESTS ---- #

# ------- SIMPLE MATH TESTS ---- #
  pln
  "Simple Math" pstrln
  pln
  # ADD #
    #G# 1 1
    #W# add
    #T# 2 eq
        "ADD: Adds top 2 numbers and puts result on the stack" test.assert
    dropstack

  # SUMALL #
    #G# 1 1 1 1 1 
    #W# sumall
    #T# 5 eq
        "SUMALL: Adds all the numbers on the stack and leaves the result on the stack" test.assert
    dropstack

  # SUB #
    #G# 3 2
    #W# sub
    #T# -1 eq
        "SUB: Subtracts top 2 numbers and puts result on the stack: a b sub = b - a" test.assert
    dropstack

  # MUL #
    #G# 2 3
    #W# mul
    #T# 6 eq
        "MUL: Multiplies top 2 numbers and puts result on the stack" test.assert
    dropstack

  # MULALL #
    #G# 2 3 4
    #W# mulall
    #T# 24 eq
        "MULALL: Multiplies all the numbers on the stack and leaves result on the stack" test.assert
    dropstack

  # DIV #
    #G# 2 4
    #W# div
    #T# 2 eq
        "DIV: Divides top 2 numbers and puts result on the stack: a b div = b / a" test.assert
    dropstack

  # SQRT #
    #G# 25
    #W# sqrt
    #T# 5 eq
        "SQRT: Gets the square root of a number on the stack" test.assert
    dropstack

  # MOD #
    #G# 2 4
    #W# MOD
    #T# 0 eq
        "MOD: Gets modulus: a b mod = b mod a" test.assert
    #G# 2 3
    #W# MOD
    #T# 1 eq
        "MOD: Gets modulus: a b mod = b mod a (2 - Odd Case)" test.assert
    dropstack
# ------ END SIMPLE MATH TESTS -------- #


pln
pequals
pln
"Tests Completed Successfully." pstr_grn pln
test_checks itostr pstr_yel
" manual checks to be made." pstr_yel pln
