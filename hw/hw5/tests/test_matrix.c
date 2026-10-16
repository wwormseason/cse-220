/*
 * CSE 220 Homework 5 tests.
 *
 * Name:
 * SBU ID:
 *
 * A few sample tests are given so you can see how Criterion and the provided
 * helpers are used. They fail until you implement the functions, which is
 * expected.
 *
 * You must add your own tests: at least 5 for each of the 4 functions, so 20
 * in total. Check the output matrix, not only the return value, and cover the
 * edge cases: a 1 by 1 matrix, a matrix of all zeros, an output matrix that is
 * too small, and inputs whose dimensions do not match.
 *
 * Build and run these with:   make test
 */
#include <criterion/criterion.h>
#include "matrix.h"
#include "matrixHelpers.h"

Test(SparseMatrix, counts_and_stores_non_zero_entries)
{
    const int D[2] = {4, 2};
    const int M[4][2] = {{0, 4}, {0, 5}, {0, 0}, {2, 0}};
    int S[3][4] = {{0}};
    int expected[3][4] = {{0, 1, 3, 0}, {1, 1, 0, 0}, {4, 5, 2, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 3);
    cr_assert(matricesEqual(3, 4, S, expected));
}

Test(SparseMatrix, reports_a_matrix_that_is_not_sparse)
{
    const int D[2] = {4, 4};
    const int M[4][4] = {{2, 3, 0, 5}, {3, 0, 3, 1}, {4, 0, 3, 0}, {0, 0, 6, 0}};
    int S[3][4] = {{0}};
    int zeros[3][4] = {{0}};

    cr_assert_eq(SparseMatrix(D, M, S), -1);
    cr_assert(matricesEqual(3, 4, S, zeros));
}

Test(HadamardProduct, multiplies_element_by_element)
{
    const int D[6] = {2, 3, 2, 3, 2, 3};
    const int M[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const int N[2][3] = {{2, 3, 4}, {5, 6, 7}};
    int A[2][3] = {{0}};
    int expected[2][3] = {{2, 6, 12}, {20, 30, 42}};

    cr_assert_eq(HadamardProduct(D, M, N, A), 1);
    cr_assert(matricesEqual(2, 3, A, expected));
}

Test(Multiplication, multiplies_two_compatible_matrices)
{
    const int D[6] = {3, 2, 2, 3, 3, 3};
    const int M[3][2] = {{2, 3}, {5, 4}, {2, 3}};
    const int N[2][3] = {{3, 2, 1}, {1, 3, 4}};
    int A[3][3] = {{0}};
    int expected[3][3] = {{9, 13, 14}, {19, 22, 21}, {9, 13, 14}};

    cr_assert_eq(Multiplication(D, M, N, A), 1);
    cr_assert(matricesEqual(3, 3, A, expected));
}

Test(DiagonalSum, sums_a_square_matrix)
{
    const int D[4] = {3, 3, 5, 3};
    const int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int DS[5][3] = {{0}};
    int expected[5][3] = {{15, 15, 0}, {12, 15, 18}, {6, 0, 0}, {15, 0, 0}, {24, 0, 0}};

    cr_assert_eq(DiagonalSum(D, A, DS), 1);
    cr_assert(matricesEqual(5, 3, DS, expected));
}

/*
 * TODO: add your own tests below.
 *
 * You still need more tests for all four functions. Useful assertions:
 *   cr_assert_eq(actual, expected)                       two values are equal
 *   cr_assert(matricesEqual(rows, cols, got, expected))  a whole matrix matches
 *   cr_assert(condition)                                 the condition is true
 *
 * printMatrix("A after the call", 2, 3, A) prints a matrix while you debug.
 */

Test(SparseMatrix, sparse_non_square_entry)
{
    const int D[2] = {2, 5};
    const int M[2][5] = {{0, 0, 3, 0, 0}, {0, 7, 0, 0, 1}};
    int S[3][5] = {{0}};
    int expected[3][5] = {{0, 1, 1, 0, 0}, {2, 1, 4, 0, 0}, {3, 7, 1, 0, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 3);
    cr_assert(matricesEqual(3, 5, S, expected));
}

Test(SparseMatrix, sparse_square_entry)
{
    const int D[2] = {3, 3};
    const int M[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int S[3][3] = {{0}};
    int expected[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 0);
    cr_assert(matricesEqual(3, 3, S, expected));
}

Test(SparseMatrix, sparse_single_entry)
{
    const int D[2] = {1, 1};
    const int M[1][1] = {{5}};
    int S[3][1] = {{0}};
    int expected[3][1] = {{0}, {0}, {5}};

    cr_assert_eq(SparseMatrix(D, M, S), 1);
    cr_assert(matricesEqual(3, 1, S, expected));
}

Test(SparseMatrix, sparse_extremely_rectangular)
{
    const int D[2] = {1, 9};
    const int M[9][1] = {{5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}};
    int S[3][9] = {{0}};
    int expected[3][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {5, 6, 7, 8, 9, 10, 11, 12, 13}};

    cr_assert_eq(SparseMatrix(D, M, S), 9);
    cr_assert(matricesEqual(3, 9, S, expected));
}

Test(SparseMatrix, sparse_whoa_i_spilled_my_numbers)
{
    const int D[2] = {2, 3};
    const int M[2][3] = {{0, 5, 0}, {0, 0, 8}};
    int S[3][3] = {{0}};
    int expected[3][3] = {{0, 1, 0}, {1, 2, 0}, {5, 8, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 2);
    cr_assert(matricesEqual(3, 3, S, expected));
}

Test(SparseMatrix, sparse_diagonally_dominant)
{
    const int D[2] = {3, 3};
    const int M[3][3] = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    int S[3][3] = {{0}};
    int expected[3][3] = {{0, 1, 2}, {0, 1, 2}, {1, 2, 3}};

    cr_assert_eq(SparseMatrix(D, M, S), 3);
    cr_assert(matricesEqual(3, 3, S, expected));
}

Test(SparseMatrix, sparse_non_sparse_two_by_three)
{
    const int D[2] = {2, 3};
    const int M[2][3] = {{1, 2, 0}, {3, 4, 0}};
    int S[3][3] = {{0}};
    int expected[3][3] = {{0}};

    cr_assert_eq(SparseMatrix(D, M, S), -1);
    cr_assert(matricesEqual(3, 3, S, expected));
}

Test(SparseMatrix, sparse_column_dominant)
{
    const int D[2] = {2, 4};
    const int M[2][4] = {{0, 0, 9, 0}, {7, 0, 0, 0}};
    int S[3][4] = {{0}};
    int expected[3][4] = {{0, 1, 0, 0}, {2, 0, 0, 0}, {9, 7, 0, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 2);
    cr_assert(matricesEqual(3, 4, S, expected));
}

Test(SparseMatrix, sparse_large_negative_value)
{
    const int D[2] = {2, 2};
    const int M[2][2] = {{-999, 0}, {0, -42}};
    int S[3][2] = {{0}};
    int expected[3][2] = {{0, 1}, {0, 1}, {-999, -42}};

    cr_assert_eq(SparseMatrix(D, M, S), 2);
    cr_assert(matricesEqual(3, 2, S, expected));
}

Test(SparseMatrix, sparse_also_extremely_rectangular)
{
    const int D[2] = {5, 1};
    const int M[5][1] = {{0}, {3}, {0}, {6}, {9}};
    int S[3][5] = {{0}};
    int expected[3][5] = {{1, 3, 4, 0, 0}, {0, 0, 0, 0, 0}, {3, 6, 9, 0, 0}};

    cr_assert_eq(SparseMatrix(D, M, S), 3);
    cr_assert(matricesEqual(3, 5, S, expected));
}

Test(SparseMatrix, sparse_all_ones)
{
    const int D[2] = {3, 3};
    const int M[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int S[3][3] = {{0}};
    int expected[3][3] = {{0}};

    cr_assert_eq(SparseMatrix(D, M, S), -1);
    cr_assert(matricesEqual(3, 3, S, expected));
}

Test(HadamardProduct, hadamard_two_squares_two)
{
    const int D[6] = {2, 2, 2, 2, 3, 3};
    const int M[2][2] = {{1, 2}, {5, 6}};
    const int N[2][2] = {{3, 4}, {7, 8}};
    int A[3][3] = {{0}};
    int expected[3][3] = {{3, 8, 0}, {35, 48, 0}, {0, 0, 0}};

    cr_assert_eq(HadamardProduct(D, M, N, A), 2);
    cr_assert(matricesEqual(3, 3, A, expected));
}

Test(HadamardProduct, hadamard_two_rectangles_two)
{
    const int D[6] = {2, 3, 2, 3, 3, 3};
    const int M[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const int N[2][3] = {{4, 5, 6}, {7, 8, 9}};
    int A[3][3] = {{0}};
    int expected[3][3] = {{4, 10, 18}, {28, 40, 54}, {0, 0, 0}};

    cr_assert_eq(HadamardProduct(D, M, N, A), 2);
    cr_assert(matricesEqual(3, 3, A, expected));
}

Test(HadamardProduct, hadamard_differently_sized_squares_neg_one)
{
    const int D[6] = {3, 3, 2, 2, 3, 3};
    const int M[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const int N[2][2] = {{2, 5}, {1, 4}};
    int A[3][3] = {{0}};
    int expected[3][3] = {{2, 10, 0}, {4, 20, 0}, {0, 0, 0}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -1);
    cr_assert(matricesEqual(3, 3, A, expected));
}

Test(HadamardProduct, hadamard_more_differently_sized_squares_neg_one)
{
    const int D[6] = {3, 3, 2, 2, 2, 2};
    const int M[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const int N[2][2] = {{2, 5}, {1, 4}};
    int A[2][2] = {{0}};
    int expected[2][2] = {{2, 10}, {4, 20}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -1);
    cr_assert(matricesEqual(2, 2, A, expected));
}

Test(HadamardProduct, hadamard_two_rectangles_neg_three)
{
    const int D[6] = {2, 3, 2, 3, 1, 2};
    const int M[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const int N[2][3] = {{2, 3, 4}, {5, 6, 7}};
    int A[1][2] = {{0}};
    int expected[1][2] = {{2, 6}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -3);
    cr_assert(matricesEqual(1, 2, A, expected));
}

Test(HadamardProduct, hadamard_two_small_squares_one)
{
    const int D[6] = {1, 1, 1, 1, 1, 1};
    const int M[1][1] = {{3}};
    const int N[1][1] = {{4}};
    int A[1][1] = {{0}};
    int expected[1][1] = {{12}};

    cr_assert_eq(HadamardProduct(D, M, N, A), 1);
    cr_assert(matricesEqual(1, 1, A, expected));
}

Test(HadamardProduct, hadamard_two_large_rectangles_neg_one)
{
    const int D[6] = {1, 5, 5, 1, 1, 1};
    const int M[1][5] = {{2, 9, 9, 9, 9}};
    const int N[5][1] = {{3}, {9}, {9}, {9}, {9}};
    int A[1][1] = {{0}};
    int expected[1][1] = {{6}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -1);
    cr_assert(matricesEqual(1, 1, A, expected));
}

Test(HadamardProduct, hadamard_two_transposed_rectangles_neg_two)
{
    const int D[6] = {3, 4, 4, 3, 5, 2};
    const int M[3][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    const int N[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    int A[5][2] = {{0}};
    int expected[5][2] = {{1, 2}, {4, 5}, {7, 8}, {0, 0}, {0, 0}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -2);
    cr_assert(matricesEqual(5, 2, A, expected));
}

Test(HadamardProduct, hadamard_matrix_with_row_length_zero_neg_one)
{
    const int D[6] = {0, 3, 3, 3, 1, 1};
    const int M[0][3] = {};
    const int N[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    int A[1][1] = {{0}};
    int expected[1][1] = {{0}};

    cr_assert_eq(HadamardProduct(D, M, N, A), -2);
    cr_assert(matricesEqual(1, 1, A, expected));
}

Test(HadamardProduct, hadamard_matrix_negative_values_in_both_matrixes_one)
{
    const int D[6] = {2, 2, 2, 2, 2, 2};
    const int M[2][2] = {{-5, 0}, {2, -1}};
    const int N[2][2] = {
        {-3, 10},
        {-4, -2},
    };
    int A[2][2] = {{0}};
    int expected[2][2] = {{15, 0}, {-8, 2}};

    cr_assert_eq(HadamardProduct(D, M, N, A), 1);
    cr_assert(matricesEqual(2, 2, A, expected));
}

Test(Multiplication, mult_two_noncompatible_matrices_neg_two)
{
    const int D[6] = {3, 2, 3, 2, 2, 2};
    const int M[3][2] = {{2, 3}, {5, 4}, {2, 3}};
    const int N[3][2] = {{3, 3}, {7, 2}, {1, 5}};
    int A[2][2] = {{0}};
    int expected[2][2] = {{27, 12}, {43, 23}};

    cr_assert_eq(Multiplication(D, M, N, A), -2);
    cr_assert(matricesEqual(2, 2, A, expected));
}

Test(Multiplication, mult_two_noncompatible_matrices_neg_one)
{
    const int D[6] = {3, 2, 3, 2, 4, 3};
    const int M[3][2] = {{2, 3}, {5, 4}, {2, 3}};
    const int N[3][2] = {{3, 3}, {7, 2}, {1, 5}};
    int A[4][3] = {{0}};
    int expected[4][3] = {{27, 12, 0}, {43, 23, 0}, {27, 12, 0}, {0, 0, 0}};

    cr_assert_eq(Multiplication(D, M, N, A), -1);
    cr_assert(matricesEqual(4, 3, A, expected));
}

Test(Multiplication, mult_two_noncompatible_matrices_two)
{
    const int D[6] = {3, 2, 2, 3, 4, 4};
    const int M[3][2] = {{2, 3}, {5, 4}, {2, 3}};
    const int N[2][3] = {{3, 2, 1}, {1, 3, 4}};
    int A[4][4] = {{0}};
    int expected[4][4] = {{9, 13, 14, 0}, {19, 22, 21, 0}, {9, 13, 14, 0}, {0, 0, 0, 0}};

    cr_assert_eq(Multiplication(D, M, N, A), 2);
    cr_assert(matricesEqual(4, 4, A, expected));
}

Test(Multiplication, mult_two_noncompatible_matrices_neg_three)
{
    const int D[6] = {3, 2, 2, 3, 2, 4};
    const int M[3][2] = {{2, 3}, {5, 4}, {2, 3}};
    const int N[2][3] = {{3, 2, 1}, {1, 3, 4}};
    int A[2][4] = {{0}};
    int expected[2][4] = {{9, 13, 14, 0}, {19, 22, 21, 0}};

    cr_assert_eq(Multiplication(D, M, N, A), -3);
    cr_assert(matricesEqual(2, 4, A, expected));
}

Test(Multiplication, mult_two_small_matrices_one)
{
    const int D[6] = {1, 1, 1, 1, 1, 1};
    const int M[1][1] = {{3}};
    const int N[1][1] = {{4}};
    int A[1][1] = {{0}};
    int expected[1][1] = {{12}};

    cr_assert_eq(Multiplication(D, M, N, A), 1);
    cr_assert(matricesEqual(1, 1, A, expected));
}

Test(Multiplication, mult_two_oops_empty_one)
{
    const int D[6] = {2, 0, 0, 3, 2, 3};
    const int M[2][0] = {};
    const int N[0][3] = {};
    int A[2][3] = {{0}};
    int expected[2][3] = {{0}};

    cr_assert_eq(Multiplication(D, M, N, A), 1);
    cr_assert(matricesEqual(2, 3, A, expected));
}

Test(Multiplication, mult_oops_lost_my_rows_neg_three)
{
    const int D[6] = {3, 2, 2, 1, 1, 5};
    const int M[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    const int N[2][1] = {{3}, {2}};
    int A[1][5] = {{0}};
    int expected[1][5] = {{7, 0, 0, 0, 0}};

    cr_assert_eq(Multiplication(D, M, N, A), -3);
    cr_assert(matricesEqual(1, 5, A, expected));
}

Test(Multiplication, mult_ouch_one_off_neg_two)
{
    const int D[6] = {4, 1, 5, 3, 4, 2};
    const int M[4][1] = {{1}, {2}, {3}, {4}};
    const int N[5][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    int A[4][2] = {{0}};
    int expected[4][2] = {{1, 2}, {2, 4}, {3, 6}, {4, 8}};

    cr_assert_eq(Multiplication(D, M, N, A), -2);
    cr_assert(matricesEqual(4, 2, A, expected));
}

Test(Multiplication, mult_a_is_really_really_big_two)
{
    const int D[6] = {1, 4, 4, 1, 100, 100};
    const int M[1][4] = {{1, 2, 3, 4}};
    const int N[4][1] = {{1}, {2}, {3}, {4}};
    int A[100][100] = {{0}};
    int expected[100][100] = {{30}};

    cr_assert_eq(Multiplication(D, M, N, A), 2);
    cr_assert(matricesEqual(100, 100, A, expected));
}

Test(Multiplication, mult_negative_numbers_neg_one)
{
    const int D[6] = {4, 2, 4, 4, 4, 4};
    const int M[4][2] = {{-1, -3}, {3, 7}, {-6, 2}, {-4, 5}};
    const int N[4][4] = {{1, -2, 3, 0}, {-4, 5, -6, 3}, {-7, -8, -9, -2}, {0, 1, 2, 3}};
    int A[4][4] = {{0}};
    int expected[4][4] = {{11, -13, 15, -9}, {-25, 29, -33, 21}, {-14, 22, -30, 6}, {-24, 33, -42, 15}};

    cr_assert_eq(Multiplication(D, M, N, A), -1);
    cr_assert(matricesEqual(4, 4, A, expected));
}

Test(DiagonalSum, diagsum_sums_a_square_matrix_two)
{
    const int D[4] = {3, 3, 5, 4};
    const int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int DS[5][4] = {{0}};
    int expected[5][4] = {{15, 15, 0, 0}, {12, 15, 18, 0}, {6, 0, 0, 0}, {15, 0, 0, 0}, {24, 0, 0, 0}};

    cr_assert_eq(DiagonalSum(D, A, DS), 2);
    cr_assert(matricesEqual(5, 4, DS, expected));
}

Test(DiagonalSum, diagsum_sums_a_smaller_square_matrix_two)
{
    const int D[4] = {2, 2, 5, 4};
    const int A[2][2] = {{2, 4}, {6, 8}};
    int DS[5][4] = {{0}};
    int expected[5][4] = {{10, 10, 0, 0}, {8, 12, 0, 0}, {6, 0, 0, 0}, {14, 0, 0, 0}, {0, 0, 0, 0}};

    cr_assert_eq(DiagonalSum(D, A, DS), 2);
    cr_assert(matricesEqual(5, 4, DS, expected));
}

Test(DiagonalSum, diagsum_sums_a_larger_square_matrix_neg_one)
{
    const int D[4] = {4, 4, 2, 2};
    const int A[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 1, 2, 3}, {4, 5, 6, 7}};
    int DS[2][2] = {{0}};
    int expected[2][2] = {{16, 16}, {19, 14}};

    cr_assert_eq(DiagonalSum(D, A, DS), -1);
    printMatrix("ds: ", 2, 2, DS);
    cr_assert(matricesEqual(2, 2, DS, expected));
}