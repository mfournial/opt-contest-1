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

static void task(benchmark::State &state) {
  // Parse args
  auto length = state.range(0);

  // Sets up intel SEAPI:
  static auto domain = __itt_domain_create("main");
  __itt_resume();
  char taskname[64];
  snprintf(taskname, 128, "size: %li", length);
  auto task = __itt_string_handle_create(taskname);
  __itt_task_begin(domain, __itt_null, __itt_null, task);

  // Original task
  for (auto _ : state) {
    state.PauseTiming();
    int NUM = length;
    char flags[8192 + 1];
    long i, k;
    int count = 0;
    state.ResumeTiming();
    while (NUM--) {
      count = 0;
      for (i = 2; i <= 8192; i++) {
        flags[i] = 1;
      }
      for (i = 2; i <= 8192; i++) {
        bool res = !bool(flags[i]);
        /* remove all multiples of prime: i */
        for (k = i + i; k <= 8192; k += i) {
          flags[k] = flags[k] & res;
        }
        count = count + (!res);
      }
    }
    state.PauseTiming();
    assert(count == 1028);
    state.ResumeTiming();
  }

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

BENCHMARK(task)->Arg(170)->Arg(1700)->Arg(17000);

BENCHMARK_MAIN();
