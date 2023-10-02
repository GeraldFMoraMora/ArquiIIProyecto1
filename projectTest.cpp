#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 100;
const int numCols = 100;
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

  //std::cout << "Total sum (Single-threaded): " << totalSum << std::endl;
}

static void SumRowsSingleThreadBenchmark(benchmark::State& state) {
  while (state.KeepRunning()) {
    sum_rows_single_thread();
  }
}

BENCHMARK(SumRowsSingleThreadBenchmark);

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
    //std::cout << "Address of atomic<int> - " << &sumTotalVec[i] << '\n';
  }

  //std::cout << "Total sum: " << totalSum << std::endl;
}

static void falseSharingBench(benchmark::State& s) {
  while (s.KeepRunning()) {
    false_sharing();    
  }
}
BENCHMARK(falseSharingBench)->Unit(benchmark::kMillisecond);


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

struct alignas(64) AlignedRow {
  std::vector<int> data;

  AlignedRow() : data(numCols, 1) {}
};

std::vector<AlignedRow> matrix2(numRows);

void sumRowNoFalseSharing(int startRow, int endRow, std::atomic<int>& resultRowSum) {
  int sum = 0;
  for (int i = startRow; i <= endRow; ++i) {
    for (int j = 0; j < numCols; ++j) {
        sum += matrix2[i].data[j];
    }
  }
  resultRowSum += sum;
}

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
      sumRowNoFalseSharing(startRow, endRow, totalSum);
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
