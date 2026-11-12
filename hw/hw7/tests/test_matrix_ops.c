/*
 * CSE 220 Homework 7, your tests for the matrix operations.
 *
 * Name:
 * SBU ID:
 *
 * At least 3 tests for each of these four functions, so at least 12 here:
 *   add_mats_sf, mult_mats_sf, transpose_mat_sf, create_matrix_sf
 *
 * Worth covering: a non square matrix, a single row or column, negative
 * values, a transpose of a transpose, and for create_matrix_sf the spacing
 * variations the assignment warns about, with and without spaces around the
 * brackets and semicolons.
 *
 * copy_matrix(rows, cols, (int[]){...}) builds a matrix for you, and
 * expect_matrices_equal(m, rows, cols, (int[]){...}) checks one. Free whatever
 * you allocate, since the valgrind suites are graded.
 */
#include "test_helpers.h"
#include "matrixscript.h"

TestSuite(my_matrix_ops, .timeout=TEST_TIMEOUT);

/* Sample: addition of two small matrices. */
Test(my_matrix_ops, add_two_by_two)
{
    matrix_sf *a = copy_matrix(2, 2, (int[]){1, 2, 3, 4});
    matrix_sf *b = copy_matrix(2, 2, (int[]){10, 20, 30, 40});
    matrix_sf *c = add_mats_sf(a, b);

    expect_matrices_equal(c, 2, 2, (int[]){11, 22, 33, 44});
    free(a);
    free(b);
    free(c);
}

/* Sample: a non square product, 2x3 times 3x2 gives 2x2. */
Test(my_matrix_ops, multiply_non_square)
{
    matrix_sf *a = copy_matrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    matrix_sf *b = copy_matrix(3, 2, (int[]){7, 8, 9, 10, 11, 12});
    matrix_sf *c = mult_mats_sf(a, b);

    expect_matrices_equal(c, 2, 2, (int[]){58, 64, 139, 154});
    free(a);
    free(b);
    free(c);
}

/*
 * TODO: at least 12 more tests here, so that each of the four functions has
 * at least 3 of your own. The two samples above do not count.
 */
