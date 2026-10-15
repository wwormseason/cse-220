#include "matrix.h"
#include <stdio.h>

int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
{

  int minRows = D[0] < D[2] ? D[0] : D[2];
  int minCols = D[1] < D[3] ? D[1] : D[3];
  for (int i = 0; i < minRows; i++)
  {
    for (int j = 0; j < minCols; j++)
    {
      *(*(A + i) + j) = (*(*(M + i) + j)) * (*(*(N + i) + j));
    }
  }

  for (int i = 0; i < D[4]; i++)
  {
    printf("{");
    for (int j = 0; j < D[5]; j++)
    {
      printf("%d, ", A[i][j]);
    }
    printf("}");
  }

  if (D[0] == D[2] && D[1] == D[3])
  {
    // compatible
    if (D[0] == D[4] && D[1] == D[5])
    {
      // A is exactly the size of the result
      return 1;
    }
    else if (D[0] <= D[4] && D[1] <= D[5])
    {
      // A is larger than M and N in both dimensions
      return 2;
    }
    else
    {
      // A is smaller than M and N in either dimension
      return -3;
    }
  }
  else
  {
    // not compatible
    if (D[4] >= minRows && D[5] >= minCols)
    {
      // A can store entire result
      return -1;
    }
    else
    {
      // A can't store entire result
      return -2;
    }
  }
}