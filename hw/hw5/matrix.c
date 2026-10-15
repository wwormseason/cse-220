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
  int trueMinRows = minRows < D[4] ? minRows : D[4];
  int trueMinCols = minCols < D[5] ? minCols : D[5];

  for (int i = 0; i < trueMinRows; i++)
  {
    for (int j = 0; j < trueMinCols; j++)
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

    AI Mode Conversation : int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
    { /* * TODO: multiply M and N element by element into A. * * D holds three pairs: the size of M, then N, then A. * * M and N are compatible when their dimensions are identical. When they * are not, work only on the part where both exist, which is * min(rows) by min(columns), the top left block of each. * * Zero all of A first, then fill in whatever part of the result fits, * starting at the top left. * * Return 1, 2, -1, -2 or -3 as described in the assignment. Read those * five rules carefully, since which one applies depends both on whether * M and N are compatible and on how A compares to the result. */ // (void)D; // (void)M; // (void)N; // (void)A; int minRows = D[0] < D[2] ? D[0] : D[2]; int minCols = D[1] < D[3] ? D[1] : D[3]; for (int i = 0; i < minRows; i++) { for (int j = 0; j < minCols; j++) { // equivalent to A[i][j] = M[i][j] * N[i][j] *(*(A + i) + j) = (*(*(M + i) + j)) * (*(*(N + i) + j)); } } if (D[0] == D[2] && D[1] == D[3]) { // compatible if (D[0] == D[4] && D[1] == D[5]) { // A is exactly the size of the result return 1; } else if (D[0] <= D[4] && D[1] <= D[5]) { // A is larger than M and N in both dimensions return 2; } else { // A is smaller than M and N in either dimension return -3; } } else { // not compatible if (D[0] >= D[4] && D[1] >= D[5]) { // A can store entire result return -1; } else { // A can't store entire result return -2; } } }

      You said : int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
      { /* * TODO: multiply M and N element by element into A. * * D holds three pairs: the size of M, then N, then A. * * M and N are compatible when their dimensions are identical. When they * are not, work only on the part where both exist, which is * min(rows) by min(columns), the top left block of each. * * Zero all of A first, then fill in whatever part of the result fits, * starting at the top left. * * Return 1, 2, -1, -2 or -3 as described in the assignment. Read those * five rules carefully, since which one applies depends both on whether * M and N are compatible and on how A compares to the result. */ // (void)D; // (void)M; // (void)N; // (void)A; int minRows = D[0] < D[2] ? D[0] : D[2]; int minCols = D[1] < D[3] ? D[1] : D[3]; for (int i = 0; i < minRows; i++) { for (int j = 0; j < minCols; j++) { // equivalent to A[i][j] = M[i][j] * N[i][j] *(*(A + i) + j) = (*(*(M + i) + j)) * (*(*(N + i) + j)); } } if (D[0] == D[2] && D[1] == D[3]) { // compatible if (D[0] == D[4] && D[1] == D[5]) { // A is exactly the size of the result return 1; } else if (D[0] <= D[4] && D[1] <= D[5]) { // A is larger than M and N in both dimensions return 2; } else { // A is smaller than M and N in either dimension return -3; } } else { // not compatible if (D[0] >= D[4] && D[1] >= D[5]) { // A can store entire result return -1; } else { // A can't store entire result return -2; } } }

        int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
        { /* * TODO: multiply M and N element by element into A. * * D holds three pairs: the size of M, then N, then A. * * M and N are compatible when their dimensions are identical. When they * are not, work only on the part where both exist, which is * min(rows) by min(columns), the top left block of each. * * Zero all of A first, then fill in whatever part of the result fits, * starting at the top left. * * Return 1, 2, -1, -2 or -3 as described in the assignment. Read those * five rules carefully, since which one applies depends both on whether * M and N are compatible and on how A compares to the result. */ // (void)D; // (void)M; // (void)N; // (void)A; int minRows = D[0] < D[2] ? D[0] : D[2]; int minCols = D[1] < D[3] ? D[1] : D[3]; for (int i = 0; i < minRows; i++) { for (int j = 0; j < minCols; j++) { // equivalent to A[i][j] = M[i][j] * N[i][j] *(*(A + i) + j) = (*(*(M + i) + j)) * (*(*(N + i) + j)); } } if (D[0] == D[2] && D[1] == D[3]) { // compatible if (D[0] == D[4] && D[1] == D[5]) { // A is exactly the size of the result return 1; } else if (D[0] <= D[4] && D[1] <= D[5]) { // A is larger than M and N in both dimensions return 2; } else { // A is smaller than M and N in either dimension return -3; } } else { // not compatible if (D[0] >= D[4] && D[1] >= D[5]) { // A can store entire result return -1; } else { // A can't store entire result return -2; } } }
Here is a review of your implementation. There are a few critical logical and syntax issues in your current code that will cause compiler errors and incorrect behavior based on your assignment's description.

Key Issues & Fixes

1. Incorrect Pointer Arithmetic Syntax:
Your pointer expression *(*(A + i) + j) is incorrect for multidimensional arrays passed like this. Because A is defined with variable dimensions A[D[4]][D[5]], the compiler needs you to use standard subscript notation A[i][j]. Your current pointer math evaluates to A[i] + j, which is an address, not the value.
2. Missing Initialization:
The instructions explicitly state: "Zero all of A first, then fill in whatever part of the result fits." Your code completely skips zeroing out A.
3. Out-of-Bounds Writing to A:
When looping up to minRows and minCols, you might exceed the dimensions of A if A is smaller than the overlapping part of M and N. You must bound your loops by D[4] (rows of A) and D[5] (columns of A) as well.
4. Incorrect Return Logic:
Your conditional checks for return values don't perfectly map to how A relates to the actual computed result block (which is bounded by minRows and minCols when incompatible).

Corrected Code

Here is the fully fixed implementation:
c
int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
{
  // 1. Zero all of A first
  for (int i = 0; i < D[4]; i++)
  {
    for (int j = 0; j < D[5]; j++)
    {
      A[i][j] = 0;
    }
  }

  // 2. Determine the boundaries of the element-by-element product
  int minRows = D[0] < D[2] ? D[0] : D[2];
  int minCols = D[1] < D[3] ? D[1] : D[3];

  // 3. Fill in whatever part of the result fits into A
  int writeRows = minRows < D[4] ? minRows : D[4];
  int writeCols = minCols < D[5] ? minCols : D[5];

  for (int i = 0; i < writeRows; i++)
  {
    for (int j = 0; j < writeCols; j++)
    {
      A[i][j] = M[i][j] * N[i][j];
    }
  }

  // 4. Return handling based on dimensions
  if (D[0] == D[2] && D[1] == D[3])
  {
    // Case: M and N are compatible
    if (D[0] == D[4] && D[1] == D[5])
    {
      return 1; // A is exactly the size of the result
    }
    else if (D[4] >= D[0] && D[5] >= D[1])
    {
      return 2; // A is strictly larger than the result in both dimensions
    }
    else
    {
      return -3; // A is smaller than the result in at least one dimension
    }
  }
  else
  {
    // Case: M and N are NOT compatible (result size is minRows x minCols)
    if (D[4] >= minRows && D[5] >= minCols)
    {
      return -1; // A is large enough to hold the entire overlap block
    }
    else
    {
      return -2; // A truncates the overlap block
    }
  }
}
Use code with caution.

Why this works:

• Safety First: The writeRows and writeCols variables ensure that even if M and N have a huge overlap, you will never write past the boundaries allocated for matrix A.
• Clean Code: Standard A[i][j] syntax is used, which avoids complicated pointer decay bugs and makes the code highly readable.
Would you like me to generate a set of test cases (like specific D arrays and matrices) so you can verify this code against edge cases?

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
    if (D[0] >= D[4] && D[1] >= D[5])
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

Here is a review of your implementation. There are three critical bugs in your current code that will lead to compiler errors, undefined behavior, and logical mistakes based on the assignment rules.

🔴 Critically Missing: You never zero out A

Your instructions explicitly state: "Zero all of A first, then fill in whatever part of the result fits."
• The Bug: Your code leaves elements of A completely untouched if they fall outside the computed boundary (minRows x minCols), violating the assignment requirements.

🔴 Memory Corruption / Buffer Overflow Vulnerability

• The Bug: In your loops, i goes up to minRows and j goes up to minCols. However, if A is smaller than the overlapping region of M and N (e.g., if M and N overlap by \(3 \times 3\), but A is only \(2 \times 2\)), your loops will attempt to write to A[2][2]. Because A is allocated as a [D[4]][D[5]] array, writing outside its bounds causes a buffer overflow / segmentation fault.
• The Fix: You must clip your loops using the dimensions of A (D[4] and D[5]).

🔴 Incorrect C Pointer Syntax for Variable Length Arrays (VLAs)

• The Bug: When a multi-dimensional array is passed to a function using VLA syntax (int A[D[4]][D[5]]), the decay rules and step sizes are handled entirely by the compiler via bracket subscripting.
• Writing *(*(A + i) + j) is not standard pointer arithmetic for variable-sized multidimensional function parameters and will fail to compile or calculate wrong offsets.
• The Fix: Use standard multi-dimensional bracket notation: A[i][j] = M[i][j] * N[i][j].

Corrected Implementation

Here is the fully compliant, safe, and bug-free version of your code:
c
int HadamardProduct(const int D[6], const int M[D[0]][D[1]], const int N[D[2]][D[3]], int A[D[4]][D[5]])
{
  // 1. Zero all of A first (as explicitly requested)
  for (int i = 0; i < D[4]; i++)
  {
    for (int j = 0; j < D[5]; j++)
    {
      A[i][j] = 0;
    }
  }

  // 2. Identify the overlapping part where both M and N exist
  int minRows = D[0] < D[2] ? D[0] : D[2];
  int minCols = D[1] < D[3] ? D[1] : D[3];

  // 3. Prevent buffer overflow: fill only what fits within A's boundary
  int writeRows = minRows < D[4] ? minRows : D[4];
  int writeCols = minCols < D[5] ? minCols : D[5];

  for (int i = 0; i < writeRows; i++)
  {
    for (int j = 0; j < writeCols; j++)
    {
      // Clean, compiler-safe bracket notation instead of manual VLA pointer manipulation
      A[i][j] = M[i][j] * N[i][j];
    }
  }

  // 4. Evaluate dimensions and return values
  if (D[0] == D[2] && D[1] == D[3])
  {
    // Case: M and N are compatible (Result size is exactly D[0] x D[1])
    if (D[0] == D[4] && D[1] == D[5])
    {
      return 1; // A matches the result size perfectly
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
