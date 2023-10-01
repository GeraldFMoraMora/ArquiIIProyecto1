#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>

const int numRows = 4;
const int numCols = 4;
std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

void sum_rows_single_thread() {
  std::vector<int> rowSums(numRows, 0);

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      rowSums[i] += matrix[i][j];
    }
  } //[4,4,4,4]

  int totalSum = 0;
  for (int i = 0; i < numRows; ++i) {
    totalSum += rowSums[i];
  } //totalSum=4+4+4+4=16

  std::cout << "Total sum (Single-threaded): " << totalSum << std::endl;
}

static void SumRowsSingleThreadBenchmark(benchmark::State& state) {
  while (state.KeepRunning()) {
    sum_rows_single_thread();
  }
}

BENCHMARK(SumRowsSingleThreadBenchmark);

BENCHMARK_MAIN();

