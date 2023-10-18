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


void diff_var_local() {
  std::vector<std::atomic<int>> intVec(int_per_line);
  std::vector<std::thread> threadVec;
  thread_local std::atomic<int> a;

  for (int i = 0; i < int_per_line; i++) {
    intVec[i] = 0;
  }

  for (int i = 0; i < num_threads; i++) {
    threadVec.emplace_back([&]() { 
      for(int j = 0; j < int_per_thread; j++){
        a = intVec[i+j].load();
        work(a); 
      }
    });
  }

  for (std::thread& thread : threadVec) {
    thread.join();
  }
}

static void noSharingLocal(benchmark::State& s) {
  while (s.KeepRunning()) {
    diff_var_local();
  }
}

BENCHMARK(noSharingLocal)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
