#include "tetris_tests.h"

int matrix_eq(int **A, int **B, int x, int y) {
  int result = 1;
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      if (A[i][j] != B[i][j]) {
        result = 0;
      }
    }
  }
  return result;
}