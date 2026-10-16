#include <stdio.h>
#include "matrix.h"

int main()
{
  // const int D[2] = {4, 2};
  // const int M[4][2] = {{0, 4}, {0, 5}, {0, 0}, {2, 0}};
  // int S[3][4] = {{0}};
  // printf("\n %d", SparseMatrix(D, M, S));

  // const int D[6] = {0, 3, 3, 3, 1, 1};
  // const int M[0][3] = {};
  // const int N[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  // int A[1][1] = {{0}};
  // printf("%d", HadamardProduct(D, M, N, A));

  // const int D[6] = {4, 2, 4, 4, 4, 4};
  // const int M[4][2] = {{-1, -3}, {3, 7}, {-6, 2}, {-4, 5}};
  // const int N[4][4] = {{1, -2, 3, 0}, {-4, 5, -6, 3}, {-7, -8, -9, -2}, {0, 1, 2, 3}};
  // int A[4][4] = {{0}};
  // printf("%d", Multiplication(D, M, N, A));

  const int D[4] = {4, 4, 2, 2};
  const int A[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 1, 2, 3}, {4, 5, 6, 7}};
  int DS[2][2] = {{0}};
  printf("%d", DiagonalSum(D, A, DS));

  return 0;
}
