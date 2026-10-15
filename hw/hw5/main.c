#include <stdio.h>
#include "matrix.h"

int main()
{
  // const int D[2] = {4, 2};
  // const int M[4][2] = {{0, 4}, {0, 5}, {0, 0}, {2, 0}};
  // int S[3][4] = {{0}};
  // printf("\n %d", SparseMatrix(D, M, S));

  const int D[6] = {2, 3, 2, 3, 1, 2};
  const int M[2][3] = {{1, 2, 3}, {4, 5, 6}};
  const int N[2][3] = {{2, 3, 4}, {5, 6, 7}};
  int A[1][2] = {{0}};
  printf("%d", HadamardProduct(D, M, N, A));

  // const int D[6] = {1, 1, 1, 1, 1, 1};
  // const int M[1][1] = {{3}};
  // const int N[1][1] = {{4}};
  // int A[1][1] = {{0}};
  // printf("%d", Multiplication(D, M, N, A));

  // const int D[4] = {3, 3, 5, 3};
  // const int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  // int DS[5][3] = {{0}};
  // printf("%d", DiagonalSum(D, A, DS));

  return 0;
}
