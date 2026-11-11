/*
 * CSE 220 Homework 6, Part 1 tests: argument validation.
 *
 * Name:
 * SBU ID:
 *
 * Write at least 10 tests of your own here. The two samples below are only
 * examples, so they do not count toward the 10. Part 1 has eight error codes
 * and an order they are checked in, so a reasonable set is one test per error
 * code, plus at least two where a command line has two faults at once and you
 * check that the higher priority one is reported.
 *
 * Helpers from test_helpers.h:
 *   prep_files(original, test_name)        copy a fixture into tests.in
 *   run_using_system_no_valgrind(name, a)  run ./bin/searchreplace with arguments a
 *   expect_error_exit(status, expected)    check the code main returned
 *   expect_outfile_matches(name)           diff the output against tests.out.exp
 *
 * Fixtures live in tests.in.orig. Never put your own files in tests.in,
 * because make test wipes it.
 */
#include "test_helpers.h"
#include "searchreplace.h"

static char args[ARGS_TEXT_LEN];

TestSuite(part1_args, .timeout = TEST_TIMEOUT);

/* Sample: too few arguments. */
Test(part1_args, missing_argument_example)
{
  char *test_name = "part1_missing_argument";
  prep_files("unix.txt", test_name);
  sprintf(args, "-s the %s/%s.in.txt %s/%s.out.txt",
          TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
  expect_error_exit(run_using_system_no_valgrind(test_name, args), MISSING_ARGUMENT);
}

/* Sample: -r is present, but the text after it is another option. */
Test(part1_args, r_argument_missing_example)
{
  char *test_name = "part1_r_missing";
  prep_files("unix.txt", test_name);
  sprintf(args, "-s the -r -l 1,5 %s/%s.in.txt %s/%s.out.txt",
          TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
  expect_error_exit(run_using_system_no_valgrind(test_name, args), R_ARGUMENT_MISSING);
}

/*
 * TODO: write at least 10 tests of your own, not counting the samples above.
 * A good set is one test per error code (MISSING_ARGUMENT, DUPLICATE_ARGUMENT,
 *   INPUT_FILE_MISSING, OUTPUT_FILE_UNWRITABLE, S_ARGUMENT_MISSING,
 *   R_ARGUMENT_MISSING, L_ARGUMENT_INVALID, WILDCARD_INVALID), a successful
 *   run, and two command lines with two faults at once.
 */
