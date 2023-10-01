#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 4;
const int numCols = 4;

struct AlignedRow {
  std::vector<int> data;

  AlignedRow() : data(numCols, 1) {}
};

std::vector<AlignedRow> matrix(numRows);

void sumRows(int startRow, int endRow, std::atomic<int>& result) {
  int sum = 0;
  for (int i = startRow; i < endRow; ++i) {
    for (int j = 0; j < numCols; ++j) {
      sum += matrix[i].data[j];
    }
  }
  result += sum;
}

void no_false_sharing_sum() {
  const int numThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(numThreads);
  std::atomic<int> totalSum(0);

  const int rowsPerThread = numRows / numThreads;
  int startRow = 0;

  for (int i = 0; i < numThreads; ++i) {
    int endRow = startRow + rowsPerThread;
    threads[i] = std::thread([&]() { sumRows(startRow, endRow, totalSum); });
    startRow = endRow;
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  std::cout << "Total sum: " << totalSum << std::endl;
}

static void noFalseSharingSolution(benchmark::State& s) {
  while (s.KeepRunning()) {
    no_false_sharing_sum();
  }
}
BENCHMARK(noFalseSharingSolution)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
