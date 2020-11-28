
#include <benchmark/benchmark.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

template <typename base_t>
void BM_classical_addition(benchmark::State& state) {
  using UBigIntegerT = UBigInteger<64, base_t>;

  for (auto _ : state) {
    UBigIntegerT val1 = 1241412;
    UBigIntegerT val2 = 123211;
    classical_addition(val1, val2, val1);
  }
}

template <typename base_t>
void BM_classical_substraction(benchmark::State& state) {
  using UBigIntegerT = UBigInteger<64, base_t>;

  for (auto _ : state) {
    UBigIntegerT val1 = 1241412;
    UBigIntegerT val2 = 123211;
    classical_substraction(val1, val2, val1);
  }
}

template <typename base_t>
void BM_classical_multiplication(benchmark::State& state) {
  using UBigIntegerT = UBigInteger<64, base_t>;

  for (auto _ : state) {
    UBigIntegerT val1 = 1241412;
    UBigIntegerT val2 = 123211;
    UBigIntegerT result;
    classical_multiplication(val1, val2, result);
  }
}

template <typename base_t>
void BM_classical_division(benchmark::State& state) {
  using UBigIntegerT = UBigInteger<64, base_t>;

  for (auto _ : state) {
    UBigIntegerT val1 = 1241412;
    UBigIntegerT val2 = 12;
    UBigIntegerT result;
    classical_division(val1, val2, result);
  }
}

BENCHMARK_TEMPLATE(BM_classical_addition, uint8_t);
BENCHMARK_TEMPLATE(BM_classical_substraction, uint8_t);
BENCHMARK_TEMPLATE(BM_classical_multiplication, uint8_t);
BENCHMARK_TEMPLATE(BM_classical_division, uint8_t);

BENCHMARK_TEMPLATE(BM_classical_addition, uint16_t);
BENCHMARK_TEMPLATE(BM_classical_substraction, uint16_t);
BENCHMARK_TEMPLATE(BM_classical_multiplication, uint16_t);
BENCHMARK_TEMPLATE(BM_classical_division, uint16_t);

BENCHMARK_TEMPLATE(BM_classical_addition, uint32_t);
BENCHMARK_TEMPLATE(BM_classical_substraction, uint32_t);
BENCHMARK_TEMPLATE(BM_classical_multiplication, uint32_t);
BENCHMARK_TEMPLATE(BM_classical_division, uint32_t);

BENCHMARK_MAIN();
