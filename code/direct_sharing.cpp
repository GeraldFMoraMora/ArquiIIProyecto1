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


void shared_var() {
  std::vector<std::thread> threadVec;

  std::atomic<int> a;
  a = 0;

  for (int i = 0; i < num_threads; i++) {
    threadVec.emplace_back([&]() { 
        for (int j = 0; j < int_per_thread; j++){ 
          work(a); 
        }
      });
  }  

  for (std::thread& thread : threadVec) {
    thread.join();
  }
}

static void directSharing(benchmark::State& s) {
  while (s.KeepRunning()) {
    shared_var();
  }
}

BENCHMARK(directSharing)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();
