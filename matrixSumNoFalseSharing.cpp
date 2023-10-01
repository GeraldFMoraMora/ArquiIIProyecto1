#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <benchmark/benchmark.h>

const int numRows = 1000;
const int numCols = 1000;

// Alinea cada fila de la matriz en un límite de caché
struct alignas(64) AlignedRow {
  std::vector<int> data;

  AlignedRow() : data(numCols, 1) {}
};

std::vector<AlignedRow> matrix(numRows);

void sumRow(int row, std::atomic<int>& result) {
  int sum = 0;
  for (int j = 0; j < numCols; ++j) {
    sum += matrix[row].data[j];
  }
  result += sum;
}

void no_false_sharing_sum() {
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

static void noFalseSharingSolution(benchmark::State& s) {
  while (s.KeepRunning()) {
    no_false_sharing_sum();    
  }
}
BENCHMARK(noFalseSharingSolution)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
