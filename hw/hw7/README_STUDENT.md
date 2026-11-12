# CSE 220 Homework 7 Starter Kit

Read the assignment description first. It has the script format, the data
structures, every function you have to write, the worked toy example and the
grading breakdown. This file only covers how to build and run things.

## What is in here

    Makefile                    builds the test runner and the aux programs
    include/matrixscript.h      the structs and prototypes, do not change
    src/matrixscript.c          write your program here
    tests/provided_tests.c      the provided tests, do not change
    tests/test_helpers.h        helpers used by the tests, do not change
    tests/test_matrix_ops.c     your tests for the four matrix functions
    tests/test_bst.c            your tests for the three BST functions
    tests/test_expressions.c    your tests for the three expression functions
    tests_aux/                  small programs the valgrind tests run
    tests.in/                   the 20 scripts the provided tests use
    tests.out.exp/              what those scripts should print

## Building and running

    make           build everything
    make test      build if needed, then run every graded test
    make valgrind  run only the valgrind checks
    make clean     remove build/, bin/ and tests.out/

The Makefile compiles with `-Wall -Wextra -Wshadow -Wdouble-promotion
-Wformat=2 -Wundef -pedantic -Werror`, so any warning stops the build. That is
deliberate: the assignment says warnings cost half your marks, so they are
errors here instead. The kit compiles as given, and almost every test fails
until you implement the functions.

To run one suite, quote the glob:

    ./bin/run_tests --filter 'my_bst/*'

## Criterion

The tests use Criterion. It is already installed in the terminal of the
CodeGrade code editor, along with gcc, make and valgrind, so `make test` and
`make valgrind` work there with no setup. Open the editor, click the terminal
icon at the bottom left, and run your commands there. Your files are the same
ones you hand in.

On your own machine, install Criterion first:

    macOS (Homebrew):   brew install criterion
    Ubuntu or Debian:   sudo apt install libcriterion-dev

The Makefile finds it through pkg-config and falls back to `-lcriterion`.

## Valgrind is graded this time

Valgrind runs your program on a simulated processor and watches every memory
access, so it finds leaks, reads of uninitialized memory and writes past the
end of a block. This assignment allocates and frees a lot, so **the valgrind
checks count toward your grade**. A valgrind test counts only when the
matching correctness test also passes.

They need Linux. On macOS or anywhere else they are skipped, so a clean run on
your laptop says nothing about the memory half of your grade. Run `make valgrind` in the
CodeGrade terminal before you hand in.

If a valgrind report is hard to read, bring it to a recitation or to your TAs
in office hours.

## What you have to write

* The ten functions in `src/matrixscript.c`. Helper functions inside that file
  are encouraged. Only that file is collected, so all of your program code has
  to be in it.
* At least 3 Criterion tests of your own for each function, which is 30 in
  total: 12 in `tests/test_matrix_ops.c`, 9 in `tests/test_bst.c` and 9 in
  `tests/test_expressions.c`. The samples already in those files do not count
  toward the minimum. Your tests are worth 25 points.
* Your name and SBU ID in a comment at the top of every file you write.

## Two things that catch people out

* **Free what you allocate.** `free_bst_sf` frees the nodes and the matrices
  they point to. `evaluate_expr_sf` frees the postfix string, the stack and
  every intermediate matrix, and returns only the result. Giving intermediate
  matrices a non alphabetical name is the easy way to tell them apart from the
  ones that live in the BST.
* **Spacing varies everywhere.** A definition may be written `A=2 2[1 2;3 4;]`
  or with spaces around every token. Expressions may have spaces anywhere. The
  postfix string you return has no spaces at all, so `A+B*C` becomes `ABC*+`.

## Submitting

You submit through CodeGrade, not as a ZIP file. Open the HW7 link on
Brightspace and CodeGrade opens with all of the files above already in its
editor. Edit `src/matrixscript.c` and the three test files there. If you built
and tested on your own machine, copy your finished versions into the editor.
Then hand in.

Do not delete or rename any file. Changes to the Makefile,
`include/matrixscript.h`, `tests/provided_tests.c` and `tests/test_helpers.h`
are ignored when your code is tested, and they are flagged for the TAs.
