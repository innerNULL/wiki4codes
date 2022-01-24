/// file: example.cpp
/// fate: 2022-01-17


#include <stdint.h>
#include <benchmark/benchmark.h>


int32_t add(int32_t a, int32_t b) {
  return a + b;
}


int32_t product(int32_t a, int32_t b) {
  return a * b;
}


static void BENCHMARK_add(benchmark::State& state) {
  for (auto _ : state) {
    add(3, 5);
  }
}


static void BENCHMARK_product(benchmark::State& state) {
  for (auto _ : state) {
    product(3, 5);
  }
}


BENCHMARK(BENCHMARK_add);
BENCHMARK(BENCHMARK_product);
BENCHMARK_MAIN();
