
#include <benchmark/benchmark.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

void BM_classical_addition(benchmark::State& state) {
  UBigInteger val1 = 1241412;
  UBigInteger val2 = 123211;

  for (auto _ : state) {
    classical_addition(val1, val2, val1);
  }
}

void BM_classical_substraction(benchmark::State& state) {
  UBigInteger val1 = 1241412;
  UBigInteger val2 = 123211;

  for (auto _ : state) {
    classical_substraction(val1, val2, val1);
  }
}

void BM_classical_multiplication(benchmark::State& state) {
  UBigInteger val1 = 1241412;
  UBigInteger val2 = 123211;
  UBigInteger result;

  for (auto _ : state) {
    classical_multiplication(val1, val2, result);
  }
}

void BM_classical_division(benchmark::State& state) {
  UBigInteger val1 = 1241412;
  UBigInteger val2 = 123211;
  UBigInteger result;

  for (auto _ : state) {
    classical_division(val1, val2, result);
  }
}

BENCHMARK(BM_classical_addition);
BENCHMARK(BM_classical_substraction);
BENCHMARK(BM_classical_multiplication);
BENCHMARK(BM_classical_division);

BENCHMARK_MAIN();
