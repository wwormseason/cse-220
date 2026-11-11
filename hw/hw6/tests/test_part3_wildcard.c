/*
 * CSE 220 Homework 6, Part 3 tests: wildcard search and replacement.
 *
 * Name:
 * SBU ID:
 *
 * Write at least 5 tests of your own here. The two samples below are only
 * examples, so they do not count toward the 5. Worth covering: a prefix
 * pattern, a suffix pattern, a word at the very start of a line, a word at the
 * end of the file, a word surrounded by punctuation, an invalid pattern, and a
 * star in the search text with no -w, which is an ordinary search.
 *
 * Quote your patterns. These tests reach your program through system(), so an
 * unquoted *n is expanded by the shell against the working directory, where it
 * happily matches the bin folder.
 */
#include "test_helpers.h"
#include "searchreplace.h"

static char args[ARGS_TEXT_LEN];

TestSuite(part3_wildcard, .timeout = TEST_TIMEOUT);

/* Sample: a pattern with no star at all, while -w asks for wildcard matching. */
Test(part3_wildcard, wildcard_invalid_example)
{
  char *test_name = "part3_wildcard_invalid";
  prep_files("unix.txt", test_name);
  sprintf(args, "-s the -w -r END %s/%s.in.txt %s/%s.out.txt",
          TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
  expect_error_exit(run_using_system_no_valgrind(test_name, args), WILDCARD_INVALID);
}

/* Sample: a prefix pattern, quoted so the shell leaves it alone. */
Test(part3_wildcard, prefix_pattern_runs)
{
  char *test_name = "part3_prefix";
  prep_files("unix.txt", test_name);
  sprintf(args, "-s 'th*' -w -r END %s/%s.in.txt %s/%s.out.txt",
          TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
  expect_normal_exit(run_using_system_no_valgrind(test_name, args));
  expect_outfile_matches(test_name);
}

/*
 * TODO: write at least 5 tests of your own, not counting the samples above,
 * and check output contents, not just return values. See the word boundary list in Part 3 of the assignment.
 */
