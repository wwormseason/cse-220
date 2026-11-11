/*
 * CSE 220 Homework 6, Part 2 tests: simple search and replacement.
 *
 * Name:
 * SBU ID:
 *
 * Write at least 5 tests of your own here. The sample below is only an
 * example, so it does not count toward the 5. Worth covering: a replacement
 * that changes the length of the line, a search term that appears inside a
 * longer word, a term that appears several times on one line, a line range
 * that starts and ends on the same line, and a range whose end is past the end
 * of the file.
 *
 * A test that checks the output file needs an expected file at
 * tests.out.exp/<test_name>.out.txt. Write it by hand, or generate it with a
 * command you trust and read it carefully before saving it.
 */
#include "test_helpers.h"
#include "searchreplace.h"

static char args[ARGS_TEXT_LEN];

TestSuite(part2_simple, .timeout = TEST_TIMEOUT);

/* Sample: a run that should succeed. Add an expected output file to check it. */
Test(part2_simple, successful_run_returns_zero)
{
  char *test_name = "part2_success";
  prep_files("unix.txt", test_name);
  sprintf(args, "-s the -r END %s/%s.in.txt %s/%s.out.txt",
          TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
  expect_normal_exit(run_using_system_no_valgrind(test_name, args));
  expect_outfile_matches(test_name);
}

/*
 * TODO: write at least 5 tests of your own, not counting the sample above.
 *
 * To check the contents as well as the return value, add
 * tests.out.exp/<your_test_name>.out.txt and call
 * expect_outfile_matches(test_name) after the run.
 */
