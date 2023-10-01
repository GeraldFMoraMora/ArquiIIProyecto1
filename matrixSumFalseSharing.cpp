#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 4;
const int numCols = 4;
std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

void sumRow(int startRow, std::atomic<int>& resultRowSum) {
  int sum = 0;
  for (int j = 0; j < numCols; ++j) {
    sum += matrix[startRow][j];
  }
  resultRowSum += sum;
}

void false_sharing() {
  std::vector<std::thread> threads(numRows);// 4 Threads
  std::atomic<int> totalSum(0);
  std::vector<std::atomic<int>> sumTotalVec(numRows);

  int numThreads = numRows;
  int startRow = 0;

  for (int i = 0; i < numThreads; ++i) {
    threads[i] = std::thread([i, &sumTotalVec, &totalSum]() { sumRow(i, sumTotalVec[i]); });
    startRow += 1;
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  for (int i = 0; i < numRows; ++i) {
    totalSum+=sumTotalVec[i];
    std::cout << "Address of atomic<int> a - " << &sumTotalVec[i] << '\n';
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
