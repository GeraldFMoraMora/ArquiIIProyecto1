#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 100;
const int numCols = 100;

struct alignas(64) AlignedRow {
  std::vector<int> data;

  AlignedRow() : data(numCols, 1) {}
};

std::vector<AlignedRow> matrix(numRows);

void sumRow(int startRow, int endRow, std::atomic<int>& resultRowSum) {
  int sum = 0;
  for (int i = startRow; i <= endRow; ++i) {
    for (int j = 0; j < numCols; ++j) {
        sum += matrix[i].data[j];
    }
  }
  resultRowSum += sum;
}

struct alignas(64) AlignedType {
  AlignedType() { val = 0; }
  std::atomic<int> val;
};

void no_false_sharing() {
  
  std::atomic<int> totalSum(0);
  std::vector<AlignedType> sumTotalVec(numRows);

  int numThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(numThreads);

  int rowsPerThread = numRows / numThreads;

  for (int i = 0; i < numThreads; ++i) {
    int startRow = i * rowsPerThread;
    int endRow = (i == numThreads - 1) ? numRows - 1 : startRow + rowsPerThread - 1;
    
    threads[i] = std::thread([startRow, endRow, &totalSum]() {
      sumRow(startRow, endRow, totalSum);
    });
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }
}

static void noFalseSharingSolution(benchmark::State& s) {
  while (s.KeepRunning()) {
    no_false_sharing();
  }
}
BENCHMARK(noFalseSharingSolution)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
