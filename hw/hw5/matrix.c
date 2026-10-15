/*
 * CSE 220 Homework 5: matrix operations with pointer arithmetic.
 *
 * Name:
 * SBU ID:
 *
 * Implement the four functions below. Inside these functions every matrix
 * element must be read and written with pointer arithmetic, so write
 * *(*(M + i) + j) rather than M[i][j]. Reading the dimensions array as D[0]
 * is fine.
 *
 * Do not change matrix.h, matrixHelpers.h or matrixHelpers.c, and do not call
 * the helper functions from this file. They are for your tests.
 *
 * Remove the (void) lines as you fill each function in. They are only there so
 * the starter kit compiles with -Werror before you have written any code.
 */
#include "matrix.h"

int SparseMatrix(const int D[2], const int M[D[0]][D[1]],
                 int S[3][(D[1] > D[0] ? D[1] : D[0])])
{
  /*
   * TODO: build the sparse representation of M in S.
   *
   * maxDim is the larger of the two dimensions of M, and S is always
   * 3 by maxDim. Zero all of S first, then scan M row by row, left to
   * right. For the k th non zero entry you find, store its row index in
   * row 0 of S, its column index in row 1, and its value in row 2, all at
   * column k.
   *
   * Return the number of non zero entries, or -1 when there are more of
   * them than maxDim, in which case S stays all zeros. A matrix of all
   * zeros is sparse and returns 0.
   */
  // (void)D;
  // (void)M;
  // (void)S;
  int maxDim = D[1] > D[0] ? D[1] : D[0];
  int p, count = 0;
  for (int i = 0; i < D[0]; i++)
  {
    for (int j = 0; j < D[1]; j++)
    {
      p = *(*(M + i) + j);
      if (p != 0)
      {
        count++;
      }
    }
  }
  if (count > maxDim)
  {
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
    return count;
  }
}

int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
{
  /*
   * TODO: multiply M and N element by element into A.
   *
   * D holds three pairs: the size of M, then N, then A.
   *
   * M and N are compatible when their dimensions are identical. When they
   * are not, work only on the part where both exist, which is
   * min(rows) by min(columns), the top left block of each.
   *
   * Zero all of A first, then fill in whatever part of the result fits,
   * starting at the top left.
   *
   * Return 1, 2, -1, -2 or -3 as described in the assignment. Read those
   * five rules carefully, since which one applies depends both on whether
   * M and N are compatible and on how A compares to the result.
   */
  // (void)D;
  // (void)M;
  // (void)N;
  // (void)A;

  int minRows = D[0] < D[2] ? D[0] : D[2];
  int minCols = D[1] < D[3] ? D[1] : D[3];
  for (int i = 0; i < minRows; i++)
  {
    for (int j = 0; j < minCols; j++)
    {
      // equivalent to A[i][j] = M[i][j] * N[i][j]
      *(*(A + i) + j) = (*(*(M + i) + j)) * (*(*(N + i) + j));
    }
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

int Multiplication(const int D[6], const int M[D[0]][D[1]],
                   const int N[D[2]][D[3]], int A[D[4]][D[5]])
{
  /*
   * TODO: multiply M by N in the usual matrix sense into A.
   *
   * M and N are compatible when the columns of M equal the rows of N. The
   * result always has the rows of M and the columns of N.
   *
   * When they are not compatible, still compute a truncated product with
   * kLimit = min(columns of M, rows of N) as the length of the dot product,
   * which is the same as padding the shorter one with zeros.
   *
   * Zero all of A first, then fill in whatever part of the result fits.
   *
   * The return values follow the same five rules as HadamardProduct.
   */
  // (void)D;
  // (void)M;
  // (void)N;
  // (void)A;

  int minRows = D[0] < D[4] ? D[0] : D[4];
  int minCols = D[3] < D[5] ? D[3] : D[5];

  int kLimit = D[1] < D[2] ? D[1] : D[2];

  for (int i = 0; i < minRows; i++)
  {
    for (int j = 0; j < minCols; j++)
    {
      int sum = 0;
      for (int k = 0; k < kLimit; k++)
      {
        sum += *(*(M + i) + k) * *(*(N + k) + j);
      }
      *(*(A + i) + j) = sum;
    }
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

  return 0;
}

int DiagonalSum(const int D[4], const int A[D[0]][D[1]], int DS[D[2]][D[3]])
{
  /*
   * TODO: compute the diagonal, column and row sums of A into DS.
   *
   * Where each sum goes:
   *   DS[0][0]      the main diagonal sum
   *   DS[0][1]      the anti diagonal sum, which stays 0 unless A is square
   *   DS[1][j]      the sum of column j
   *   DS[i + 2][0]  the sum of row i
   * Everything else in DS stays 0.
   *
   * For an A with r rows and c columns, DS needs exactly r + 2 rows and
   * max(2, c) columns. Return 1 at exactly that size, 2 when DS is larger
   * in both dimensions, and -1 when it is too small in either one. When it
   * is too small, still store whatever fits, starting from the top left, so
   * guard every write against the real Asize of DS.
   */
  // (void)D;
  // (void)A;
  // (void)DS;

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
  if (square)
  {
    int antiDiagonalSum = 0;
    for (int i = minLimit - 1; i >= 0; i--)
    {
      antiDiagonalSum += *(*(A + i) + i);
    }
    *(*(DS) + 1) = antiDiagonalSum;
  }

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
  } // bel
}
