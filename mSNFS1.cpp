#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 100;
const int numCols = 100;
std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols, 1));

void sumRow(int startRow, std::atomic<int>& resultRowSum) {
  int sum = 0;
  for (int j = 0; j < numCols; ++j) {
    sum += matrix[startRow][j];
  }
  resultRowSum += sum;
}

struct alignas(64) AlignedType {
  AlignedType() { val = 0; }
  std::atomic<int> val;
};

void false_sharing_case2() {
  std::vector<std::thread> threads(numRows);// 4 Threads
  std::atomic<int> totalSum(0);
  std::vector<AlignedType> sumTotalVec(numRows);

  int numThreads = numRows;

  for (int i = 0; i < numThreads; ++i) {
    threads[i] = std::thread([i, &sumTotalVec, &totalSum]() { sumRow(i, sumTotalVec[i].val); });
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  for (int i = 0; i < numRows; ++i) {
    totalSum+=sumTotalVec[i].val.load();
    //std::cout << "Address of atomic<int> - " << &sumTotalVec[i] << '\n';
  }

  //std::cout << "Total sum: " << totalSum << std::endl;
}

static void falseSharingSolutionCase2(benchmark::State& s) {
  while (s.KeepRunning()) {
    false_sharing_case2();
  }
}
BENCHMARK(falseSharingSolutionCase2)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
