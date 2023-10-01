#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 1000;
const int numCols = 1000;
std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

void sumRow(int startRow, int endRow, std::atomic<int>& result) {
  int sum = 0;
  for (int i = startRow; i < endRow; ++i) {
    for (int j = 0; j < numCols; ++j) {
      sum += matrix[i][j];
    }
  }
  result += sum;
}

void false_sharing() {
  std::vector<std::thread> threads(numRows);
  std::atomic<int> totalSum(0);
  int numThreads = std::thread::hardware_concurrency();

  int rowsPerThread = numRows / numThreads;
  int startRow = 0;

  for (int i = 0; i < numThreads; ++i) {
    int endRow = startRow + rowsPerThread;
    threads[i] = std::thread([&]() { sumRow(startRow, endRow, totalSum); });
    startRow = endRow;
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  std::cout << "Total sum: " << totalSum << std::endl;
}

static void falseSharingBench(benchmark::State& s) {
  while (s.KeepRunning()) {
    false_sharing();    
  }
}
BENCHMARK(falseSharingBench)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
