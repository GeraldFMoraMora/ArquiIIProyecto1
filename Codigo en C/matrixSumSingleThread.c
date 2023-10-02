#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define numRows 100
#define numCols 100

int matrix[numRows][numCols];

void sum_rows_single_thread() {
  int rowSums[numRows];

  for (int i = 0; i < numRows; ++i) {
    rowSums[i] = 0;
    for (int j = 0; j < numCols; ++j) {
      rowSums[i] += matrix[i][j];
    }
  }

  int totalSum = 0;
  for (int i = 0; i < numRows; ++i) {
    totalSum += rowSums[i];
  }

  printf("Total sum (Single-threaded): %d\n", totalSum);
}

int main() {
  // Initialize the matrix with values
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      matrix[i][j] = 1;
    }
  }

  // Run the benchmark
  clock_t start_time = clock();
  sum_rows_single_thread();
  clock_t end_time = clock();
  
  // Calculate and print the execution time
  double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Execution time (Single-threaded): %f seconds\n", execution_time);

  return 0;
}
