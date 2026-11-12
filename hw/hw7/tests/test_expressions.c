/*
 * CSE 220 Homework 7, your tests for expressions and scripts.
 *
 * Name:
 * SBU ID:
 *
 * At least 3 tests for each of these three functions, so at least 9 here:
 *   infix2postfix_sf, evaluate_expr_sf, execute_script_sf
 *
 * Worth covering: the precedence of ' over * over +, parentheses that change
 * the order, a transpose applied to a parenthesised group, an expression that
 * uses the same matrix twice, and a script whose last line is a definition
 * rather than a formula.
 *
 * The postfix string contains no spaces, so "A+B*C" becomes "ABC*+". Free the
 * string that infix2postfix_sf returns, and the matrix that the other two
 * return, since the valgrind suites are graded.
 *
 * For a script test, put your own script in tests.in and pass its path to
 * execute_script_sf.
 */
#include "test_helpers.h"
#include "matrixscript.h"

TestSuite(my_expressions, .timeout=TEST_TIMEOUT);

/* Sample: multiplication binds tighter than addition. */
Test(my_expressions, postfix_respects_precedence)
{
    char infix[] = "A+B*C";
    char *postfix = infix2postfix_sf(infix);

    cr_assert_str_eq(postfix, "ABC*+");
    free(postfix);
}

/* Sample: transpose is unary and binds tightest. */
Test(my_expressions, postfix_handles_transpose)
{
    char infix[] = "(A+B)'*C";
    char *postfix = infix2postfix_sf(infix);

    cr_assert_str_eq(postfix, "AB+'C*");
    free(postfix);
}

/*
 * TODO: at least 9 more tests here, so that each of the three functions has
 * at least 3 of your own. The two samples above do not count.
 */
