#include "matrix.h"
#include <stdio.h>

int DiagonalSum(const int D[4], const int A[D[0]][D[1]], int DS[D[2]][D[3]])
{
  int minLimit = D[0] < D[1] ? D[0] : D[1];
  int square = (D[0] == D[1]);

  // diagonal
  int diagonalSum = 0;
  for (int i = 0; i < minLimit; i++)
  {
    diagonalSum += *(*(A + i) + i);
  }
  // printf("Diagonal Sum: %d\n", diagonalSum);
  *(*(DS)) = diagonalSum;

  // anti diagonal sum
  if (square)
  {
    int antiDiagonalSum = 0;
    for (int i = 0; i < minLimit; i++)
    {
      antiDiagonalSum += *(*(A + i) + (minLimit - 1 - i));
    }
    *(*(DS) + 1) = antiDiagonalSum;
  }
  // printf("Anti-Diagonal Sum: %d\n", antiDiagonalSum);

  // sum of columns
  for (int j = 0; j < D[1]; j++)
  {
    int colSum = 0;
    // printf("Column %d\n", j);
    for (int i = 0; i < D[0]; i++)
    {
      // printf("(%d, %d) %d\n", i, j, *(*(A + i) + j));
      colSum += *(*(A + i) + j);
    }
    // printf("Column %d Sum: %d\n", j, colSum);
    *(*(DS + 1) + j) = colSum;
  }

  // sum of rows
  for (int i = 0; i < D[0]; i++)
  {
    int rowSum = 0;
    for (int j = 0; j < D[1]; j++)
    {
      rowSum += *(*(A + i) + j);
    }
    // printf("Row %d Sum: %d\n", i, rowSum);
    *(*(DS + i + 2)) = rowSum;
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

  if (D[2] == D[0] + 2 && (D[1] == D[3] || D[3] == 2))
  {
    // DS has exactly D[1] + 2 rows and D[0] or 2 columns
    return 1;
  }
  else if (D[2] >= D[0] + 2 && (D[3] >= D[1] || D[3] >= 2))
  {
    // DS has greater than D[1] + 2 rows and greater than D[0] or 2 columns
    return 2;
  }
  else
  {
    return -1;
  }
}