#include "matrix.h"
#include <stdio.h>

int DiagonalSum(const int D[4], const int A[D[0]][D[1]], int DS[D[2]][D[3]])
{
  int minLimit = D[0] <= D[1] ? D[0] : D[1];
  int square = (D[0] == D[1]);

  // diagonal
  int diagonalSum = 0;
  for (int i = 0; i < D[0] && i < D[1]; i++)
  {
    diagonalSum += *(*(A + i) + i);
  }
  *(*(DS)) = diagonalSum;

  // anti diagonal sum
  int antiDiagonalSum = 0;
  if (square)
  {
    for (int i = minLimit - 1; i >= 0; i--)
    {
      antiDiagonalSum += *(*(A + i) + i);
    }
  }
  *(*(DS) + 1) = antiDiagonalSum;

  // sum of rows
  for (int i = 0; i < D[0]; i++)
  {
    int rowSum = 0;
    for (int j = 0; j < D[1]; j++)
    {
      rowSum += *(*(A + i) + j);
    }
    *(*(DS + i + 2)) = rowSum;
  }

  // sum of columns
  for (int i = 0; i < D[0]; i++)
  {
    int colSum = 0;
    for (int j = 0; j < D[1]; j++)
    {
      colSum += *(*(A + j) + i);
    }
    *(*(DS + 1) + i) = colSum;
  }

  for (int i = 0; i < D[2]; i++)
  {
    printf("{");
    for (int j = 0; j < D[3]; j++)
    {
      printf("%d, ", DS[i][j]);
    }
    printf("}");
  }

  if (D[2] == D[1] + 2 && (D[3] == D[0] || D[3] == 2))
  {
    // DS has exactly D[1] + 2 rows and D[0] or 2 columns
    return 1;
  }
  else if (D[2] > D[1] + 2 && (D[3] > D[0] || D[3] > 2))
  {
    // DS has greater than D[1] + 2 rows and greater than D[0] or 2 columns
    return 2;
  }
  else
  {
    return -1;
  }
}