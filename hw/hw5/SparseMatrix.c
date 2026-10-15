#include "matrix.h"
#include <stdio.h>

int SparseMatrix(const int D[2], const int M[D[0]][D[1]], int S[3][(D[1] > D[0] ? D[1] : D[0])])
{
  int maxDim = D[1] > D[0] ? D[1] : D[0];
  int p, count = 0;
  for (int i = 0; i < D[0]; i++)
  {
    for (int j = 0; j < D[1]; j++)
    {
      p = *(*(M + i) + j);
      // printf("%d", p);
      if (p != 0)
      {
        count++;
      }
    }
  }
  if (count > maxDim)
  {
    for (int i = 0; i < 3; i++)
    {
      printf("{");
      for (int j = 0; j < maxDim; j++)
      {
        printf("%d, ", S[i][j]);
      }
      printf("}");
    }
    return -1;
  }
  else
  {
    int k = 0;
    for (int i = 0; i < D[0]; i++)
    {
      for (int j = 0; j < D[1]; j++)
      {
        p = *(*(M + i) + j);
        if (p != 0)
        {
          *(*(S + 0) + k) = i;
          *(*(S + 1) + k) = j;
          *(*(S + 2) + k) = p;
          k++;
        }
      }
    }
    // printf("not error \n");
    for (int i = 0; i < 3; i++)
    {
      printf("{");
      for (int j = 0; j < maxDim; j++)
      {
        printf("%d, ", S[i][j]);
      }
      printf("}");
    }
    return count;
  }
}