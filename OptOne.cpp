#include <assert.h>
#include <benchmark/benchmark.h>
#include <iostream>
#include <ittnotify.h>

#ifdef BIG_PROBLEM_SIZE
#define LENGTH 170000
#else
#define LENGTH 17000
#endif

using namespace std;

static void test(benchmark::State& state) {
  // Get Args
  auto length = state.range(0);

  // Sets up intel SEA:
  static auto domain = __itt_domain_create("main");
  __itt_resume();
  char taskname[64];
  snprintf(taskname, 128, "size: %li", length);
  auto task = __itt_string_handle_create(taskname);
  __itt_task_begin(domain, __itt_null, __itt_null, task);

  int test = length;
  for (auto _ : state) {
    if (test == 0) {
      test = (test + 1) % 10;
    }
  }

  assert(test == 1);
  benchmark::DoNotOptimize(test);
  __itt_task_end(domain);
  __itt_pause();
}

void original() {
  int NUM = LENGTH;
  static char flags[8192 + 1];
  long i, k;
  int count = 0;

  while (NUM--) {
    count = 0;
    for (i = 2; i <= 8192; i++) {
      flags[i] = 1;
    }
    for (i = 2; i <= 8192; i++) {
      if (flags[i]) {
        /* remove all multiples of prime: i */
        for (k = i + i; k <= 8192; k += i) {
          flags[k] = 0;
        }
        count++;
      }
    }
  }

  cout << "Count: " << count << endl;
  assert(count == 1028);
}

BENCHMARK(test)->Arg(0)->Arg(1);

BENCHMARK_MAIN();
