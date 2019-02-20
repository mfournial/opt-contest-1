# opt-contest-1
Let's see if there is something interesting to do from https://dendibakh.github.io/blog/2019/02/16/Performance-optimization-contest-1

## Usage 

### Enable performance recording

```
sudo sh -c "echo 0 > /proc/sys/kernel/perf_event_paranoid"
```

### Run original challenge

This is what the original is doing:

```bash
$> gcc sieve.c -O3 -o sieve
$> time -p ./sieve
Count: 1028
real 4.02
user 4.02
sys 0.00
```

### Benchmarks

Assuming [Intel SEAPI](https://github.com/intel/IntelSEAPI) is build in suggested location (`/opt/intel`).

```bash
mkdir build
cd build
cmake ..
cd ..
cmake --build build
./build/OptOne
```

:warning: **Refer to [Google Benchmark's README](https://github.com/google/benchmark) (at the very bottom) if you see the following warning in the output::**
```
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
```

They currently recommend the following
```
sudo cpupower frequency-set --governor performance
./mybench
sudo cpupower frequency-set --governor powersave
```

### Run performance analyses

Apply `./vtune.patch` to eliminate the benchmark noise when analysing the performance
