#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 1000;
const int numCols = 1000;
std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

void sumRow(int row, std::atomic<int>& result) {
  int sum = 0;
  for (int j = 0; j < numCols; ++j) {
    sum += matrix[row][j];
  }
  result += sum;
}

void flase_sharing() {
  std::vector<std::thread> threads(numRows);
  std::atomic<int> totalSum(0);

  for (int i = 0; i < numRows; ++i) {
    threads[i] = std::thread([&]() { sumRow(i, totalSum); });
  }

  for (int i = 0; i < numRows; ++i) {
    threads[i].join();
  }

  std::cout << "Total sum: " << totalSum << std::endl;
}

static void falseSharingBench(benchmark::State& s) {
  while (s.KeepRunning()) {
    flase_sharing();    
  }
}
BENCHMARK(falseSharingBench)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();