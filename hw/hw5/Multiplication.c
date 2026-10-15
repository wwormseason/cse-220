#include "matrix.h"
#include <stdio.h>

int Multiplication(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
{

  int minRows = D[0] < D[4] ? D[0] : D[4];
  int minCols = D[3] < D[5] ? D[3] : D[5];

  printf("minRow: %d\n", minRows);
  printf("minCol: %d\n", minCols);

  int kLimit = D[1] < D[2] ? D[1] : D[2];

  printf("kLimit: %d\n", kLimit);

  for (int i = 0; i < minRows; i++)
  {
    for (int j = 0; j < minCols; j++)
    {
      int sum = 0;
      for (int k = 0; k < kLimit; k++)
      {
        sum += (*(*(M + i) + k)) * (*(*(N + k) + j));
      }
      *(*(A + i) + j) = sum;
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

  if (D[1] == D[2])
  {
    // compatible
    if (D[4] == D[0] && D[5] == D[3])
    {
      // A is exactly size of result
      return 1;
    }
    else if (D[4] > D[0] && D[5] > D[3])
    {
      // A is greater than result in both dimensions
      return 2;
    }
    else
    {
      // A is smaller than result in either dimension
      return -3;
    }
  }
  else
  {
    // not compatible
    if (D[4] >= D[0] && D[5] >= D[3])
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