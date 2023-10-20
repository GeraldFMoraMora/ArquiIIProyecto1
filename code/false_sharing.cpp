#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <unistd.h>
#include </usr/include/linux/perf_event.h>

int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
long cache_lsize = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
unsigned int num_threads = std::thread::hardware_concurrency();
const int int_per_line = cache_lsize / sizeof(std::atomic<int>);
const int int_per_thread = int_per_line / num_threads;

void work(std::atomic<int>& a) {
  for (int i = 0; i < 100000; i++) {
    a++;
  }
}

void diff_var() {
  const int num_elements = int_per_line * 2; // Doble el tamaño para aumentar el riesgo de false sharing
  std::vector<std::atomic<int>> intVec(num_elements);

  for (int i = 0; i < num_elements; i++) {
    intVec[i] = 0;
  }

  std::vector<std::thread> threadVec;
  for (int i = 0; i < num_threads; i++) {
    threadVec.emplace_back([&intVec, i]() {
      for (int j = i * int_per_thread; j < (i + 1) * int_per_thread; j++) {
        work(intVec[j]);
      }
    });
  }

  // Join the threads
  for (std::thread& thread : threadVec) {
    thread.join();
  }
}

static void falseSharing(benchmark::State& s) {
  while (s.KeepRunning()) {
    diff_var();
  }
}

BENCHMARK(falseSharing)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
