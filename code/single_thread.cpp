#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
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

void single_thread() {
  std::atomic<int> a;
  a = 0;

  for (int i = 0; i < int_per_line; i++){
    work(a);
  }
}

static void singleThread(benchmark::State& s) {
  while (s.KeepRunning()) {
    single_thread();
  }
}

BENCHMARK(singleThread)->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
