/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  if (M == 32) {
    int i, j, x, y, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;
    for (i = 0; i < M; i += 8) {
      for (j = 0; j < N; j += 8)  {

        if (i != j) {
          for (x = i; x < i + 8; ++x)
            for (y = j; y < j + 8; ++y)
              B[y][x] = A[x][y];
        }

        else {
          tmp1 = A[i][j];
          tmp2 = A[i][j + 1];
          tmp3 = A[i][j + 2];
          tmp4 = A[i][j + 3];
          tmp5 = A[i][j + 4];
          tmp6 = A[i][j + 5];
          tmp7 = A[i][j + 6];
          tmp8 = A[i][j + 7];

          B[i][j] = tmp1;
          B[i][j + 1] = tmp2;
          B[i][j + 2] = tmp3;
          B[i][j + 3] = tmp4;
          B[i][j + 4] = tmp5;
          B[i][j + 5] = tmp6;
          B[i][j + 6] = tmp7;
          B[i][j + 7] = tmp8;

          tmp1 = A[i + 1][j];
          tmp2 = A[i + 1][j + 1];
          tmp3 = A[i + 1][j + 2];
          tmp4 = A[i + 1][j + 3];
          tmp5 = A[i + 1][j + 4];
          tmp6 = A[i + 1][j + 5];
          tmp7 = A[i + 1][j + 6];
          tmp8 = A[i + 1][j + 7];

          B[i + 1][j] = B[i][j + 1];
          B[i][j + 1] = tmp1;
          B[i + 1][j + 1] = tmp2;
          B[i + 1][j + 2] = tmp3;
          B[i + 1][j + 3] = tmp4;
          B[i + 1][j + 4] = tmp5;
          B[i + 1][j + 5] = tmp6;
          B[i + 1][j + 6] = tmp7;
          B[i + 1][j + 7] = tmp8;

          tmp1 = A[i + 2][j];
          tmp2 = A[i + 2][j + 1];
          tmp3 = A[i + 2][j + 2];
          tmp4 = A[i + 2][j + 3];
          tmp5 = A[i + 2][j + 4];
          tmp6 = A[i + 2][j + 5];
          tmp7 = A[i + 2][j + 6];
          tmp8 = A[i + 2][j + 7];

          B[i + 2][j] = B[i][j + 2];
          B[i + 2][j + 1] = B[i + 1][j + 2];
          B[i][j + 2] = tmp1;
          B[i + 1][j + 2] = tmp2;
          B[i + 2][j + 2] = tmp3;
          B[i + 2][j + 3] = tmp4;
          B[i + 2][j + 4] = tmp5;
          B[i + 2][j + 5] = tmp6;
          B[i + 2][j + 6] = tmp7;
          B[i + 2][j + 7] = tmp8;

          tmp1 = A[i + 3][j];
          tmp2 = A[i + 3][j + 1];
          tmp3 = A[i + 3][j + 2];
          tmp4 = A[i + 3][j + 3];
          tmp5 = A[i + 3][j + 4];
          tmp6 = A[i + 3][j + 5];
          tmp7 = A[i + 3][j + 6];
          tmp8 = A[i + 3][j + 7];

          B[i + 3][j] = B[i][j + 3];
          B[i + 3][j + 1] = B[i + 1][j + 3];
          B[i + 3][j + 2] = B[i + 2][j + 3];
          B[i][j + 3] = tmp1;
          B[i + 1][j + 3] = tmp2;
          B[i + 2][j + 3] = tmp3;
          B[i + 3][j + 3] = tmp4;
          B[i + 3][j + 4] = tmp5;
          B[i + 3][j + 5] = tmp6;
          B[i + 3][j + 6] = tmp7;
          B[i + 3][j + 7] = tmp8;

          tmp1 = A[i + 4][j];
          tmp2 = A[i + 4][j + 1];
          tmp3 = A[i + 4][j + 2];
          tmp4 = A[i + 4][j + 3];
          tmp5 = A[i + 4][j + 4];
          tmp6 = A[i + 4][j + 5];
          tmp7 = A[i + 4][j + 6];
          tmp8 = A[i + 4][j + 7];

          B[i + 4][j] = B[i][j + 4];
          B[i + 4][j + 1] = B[i + 1][j + 4];
          B[i + 4][j + 2] = B[i + 2][j + 4];
          B[i + 4][j + 3] = B[i + 3][j + 4];
          B[i][j + 4] = tmp1;
          B[i + 1][j + 4] = tmp2;
          B[i + 2][j + 4] = tmp3;
          B[i + 3][j + 4] = tmp4;
          B[i + 4][j + 4] = tmp5;
          B[i + 4][j + 5] = tmp6;
          B[i + 4][j + 6] = tmp7;
          B[i + 4][j + 7] = tmp8;

          tmp1 = A[i + 5][j];
          tmp2 = A[i + 5][j + 1];
          tmp3 = A[i + 5][j + 2];
          tmp4 = A[i + 5][j + 3];
          tmp5 = A[i + 5][j + 4];
          tmp6 = A[i + 5][j + 5];
          tmp7 = A[i + 5][j + 6];
          tmp8 = A[i + 5][j + 7];

          B[i + 5][j] = B[i][j + 5];
          B[i + 5][j + 1] = B[i + 1][j + 5];
          B[i + 5][j + 2] = B[i + 2][j + 5];
          B[i + 5][j + 3] = B[i + 3][j + 5];
          B[i + 5][j + 4] = B[i + 4][j + 5];
          B[i][j + 5] = tmp1;
          B[i + 1][j + 5] = tmp2;
          B[i + 2][j + 5] = tmp3;
          B[i + 3][j + 5] = tmp4;
          B[i + 4][j + 5] = tmp5;
          B[i + 5][j + 5] = tmp6;
          B[i + 5][j + 6] = tmp7;
          B[i + 5][j + 7] = tmp8;

          tmp1 = A[i + 6][j];
          tmp2 = A[i + 6][j + 1];
          tmp3 = A[i + 6][j + 2];
          tmp4 = A[i + 6][j + 3];
          tmp5 = A[i + 6][j + 4];
          tmp6 = A[i + 6][j + 5];
          tmp7 = A[i + 6][j + 6];
          tmp8 = A[i + 6][j + 7];

          B[i + 6][j] = B[i][j + 6];
          B[i + 6][j + 1] = B[i + 1][j + 6];
          B[i + 6][j + 2] = B[i + 2][j + 6];
          B[i + 6][j + 3] = B[i + 3][j + 6];
          B[i + 6][j + 4] = B[i + 4][j + 6];
          B[i + 6][j + 5] = B[i + 5][j + 6];
          B[i][j + 6] = tmp1;
          B[i + 1][j + 6] = tmp2;
          B[i + 2][j + 6] = tmp3;
          B[i + 3][j + 6] = tmp4;
          B[i + 4][j + 6] = tmp5;
          B[i + 5][j + 6] = tmp6;
          B[i + 6][j + 6] = tmp7;
          B[i + 6][j + 7] = tmp8;

          tmp1 = A[i + 7][j];
          tmp2 = A[i + 7][j + 1];
          tmp3 = A[i + 7][j + 2];
          tmp4 = A[i + 7][j + 3];
          tmp5 = A[i + 7][j + 4];
          tmp6 = A[i + 7][j + 5];
          tmp7 = A[i + 7][j + 6];
          tmp8 = A[i + 7][j + 7];

          B[i + 7][j] = B[i][j + 7];
          B[i + 7][j + 1] = B[i + 1][j + 7];
          B[i + 7][j + 2] = B[i + 2][j + 7];
          B[i + 7][j + 3] = B[i + 3][j + 7];
          B[i + 7][j + 4] = B[i + 4][j + 7];
          B[i + 7][j + 5] = B[i + 5][j + 7];
          B[i + 7][j + 6] = B[i + 6][j + 7];
          B[i][j + 7] = tmp1;
          B[i + 1][j + 7] = tmp2;
          B[i + 2][j + 7] = tmp3;
          B[i + 3][j + 7] = tmp4;
          B[i + 4][j + 7] = tmp5;
          B[i + 5][j + 7] = tmp6;
          B[i + 6][j + 7] = tmp7;
          B[i + 7][j + 7] = tmp8;
        }
      }
    }
  }

  else if (M == 64) {
    int i, j, x, y, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;
    for (i = 0; i < M; i += 8) {
      for (j = 0; j < N; j += 8) {
        for (x = i; x < i + 4; ++x) {
          tmp1 = A[x][j];
          tmp2 = A[x][j + 1];
          tmp3 = A[x][j + 2];
          tmp4 = A[x][j + 3];
          tmp5 = A[x][j + 4];
          tmp6 = A[x][j + 5];
          tmp7 = A[x][j + 6];
          tmp8 = A[x][j + 7];

          B[j][x] = tmp1;
          B[j + 1][x] = tmp2;
          B[j + 2][x] = tmp3;
          B[j + 3][x] = tmp4;
          B[j][x + 4] = tmp5;
          B[j + 1][x + 4] = tmp6;
          B[j + 2][x + 4] = tmp7;
          B[j + 3][x + 4] = tmp8;
        }

        for (y = j; y < j + 4; ++y) {
          tmp1 = A[i + 4][y];
          tmp2 = A[i + 5][y];
          tmp3 = A[i + 6][y];
          tmp4 = A[i + 7][y];
          tmp5 = B[y][i + 4];
          tmp6 = B[y][i + 5];
          tmp7 = B[y][i + 6];
          tmp8 = B[y][i + 7];

          B[y][i + 4] = tmp1;
          B[y][i + 5] = tmp2;
          B[y][i + 6] = tmp3;
          B[y][i + 7] = tmp4;
          B[y + 4][i] = tmp5;
          B[y + 4][i + 1] = tmp6;
          B[y + 4][i + 2] = tmp7;
          B[y + 4][i + 3] = tmp8;
        }

        for (x = i + 4; x < i + 8; ++x) {
          tmp1 = A[x][j + 4];
          tmp2 = A[x][j + 5];
          tmp3 = A[x][j + 6];
          tmp4 = A[x][j + 7];

          B[j + 4][x] = tmp1;
          B[j + 5][x] = tmp2;
          B[j + 6][x] = tmp3;
          B[j + 7][x] = tmp4;
        }
      }
    }
  }

  else if (M == 61) {
		int i, j, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;
		int n = N / 8 * 8;
		int m = M / 8 * 8;
		for (j = 0; j < m; j += 8) {
			for (i = 0; i < n; ++i) {
				tmp1 = A[i][j];
				tmp2 = A[i][j+1];
				tmp3 = A[i][j+2];
				tmp4 = A[i][j+3];
				tmp5 = A[i][j+4];
				tmp6 = A[i][j+5];
				tmp7 = A[i][j+6];
				tmp8 = A[i][j+7];
				
				B[j][i] = tmp1;
				B[j+1][i] = tmp2;
				B[j+2][i] = tmp3;
				B[j+3][i] = tmp4;
				B[j+4][i] = tmp5;
				B[j+5][i] = tmp6;
				B[j+6][i] = tmp7;
				B[j+7][i] = tmp8;
			}
    }
		for (i = n; i < N; ++i) {
			for (j = m; j < M; ++j) {
				tmp1 = A[i][j];
				B[j][i] = tmp1;
			}
    }
		for (i = 0; i < N; ++i) {
			for (j = m; j < M; ++j) {
				tmp1 = A[i][j];
				B[j][i] = tmp1;
			}
    }
		for (i = n; i < N; ++i) {
			for (j = 0; j < M; ++j) {
				tmp1 = A[i][j];
				B[j][i] = tmp1;
			}
    }
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, tmp;

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      tmp = A[i][j];
      B[j][i] = tmp;
    }
  }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
  /* Register your solution function */
  registerTransFunction(transpose_submit, transpose_submit_desc); 

  /* Register any additional transpose functions */
  registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
  int i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; ++j) {
      if (A[i][j] != B[j][i]) {
        return 0;
      }
    }
  }
  return 1;
}

