#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

void comparison_check(uint64_t a, uint64_t b) {
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;

  EXPECT_EQ(val1 == val2, a == b);
  EXPECT_EQ(val2 == val1, b == a);

  EXPECT_EQ(val1 != val2, a != b);
  EXPECT_EQ(val2 != val1, b != a);

  EXPECT_EQ(val1 > val2, a > b);
  EXPECT_EQ(val2 > val1, b > a);

  EXPECT_EQ(val1 >= val2, a >= b);
  EXPECT_EQ(val2 >= val1, b >= a);

  EXPECT_EQ(val1 < val2, a < b);
  EXPECT_EQ(val2 < val1, b < a);

  EXPECT_EQ(val1 <= val2, a <= b);
  EXPECT_EQ(val2 <= val1, b <= a);
}

void addition_check(uint64_t a, uint64_t b) {
  a = (uint32_t)a;
  b = (uint32_t)b;
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a + b;
  EXPECT_EQ(val1 + val2, UBigInteger<64>(c));
  EXPECT_EQ(val2 + val1, UBigInteger<64>(c));
}

void substraction_check(uint64_t a, uint64_t b) {
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a - b;
  EXPECT_EQ(val1 - val2, UBigInteger<64>(c));
  EXPECT_EQ(-(val2 - val1), UBigInteger<64>(c));
  c = b - a;
  EXPECT_EQ(val2 - val1, UBigInteger<64>(c));
  EXPECT_EQ(-(val1 - val2), UBigInteger<64>(c));
  EXPECT_EQ(val2 -= val1, UBigInteger<64>(c));

  EXPECT_EQ(val1 - val1, UBigInteger<64>(0));
  EXPECT_EQ(val2 - val2, UBigInteger<64>(0));
}

void multiplication_check(uint64_t a, uint64_t b) {
  a = (uint32_t)a;
  b = (uint32_t)b;
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a * b;
  EXPECT_EQ(val1 * val2, UBigInteger<64>(c));
  EXPECT_EQ(val2 * val1, UBigInteger<64>(c));
}

void division_check1(uint64_t a, uint64_t b) {
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a / b;
  EXPECT_EQ(val1 / val2, UBigInteger<64>(c));
  c = b / a;
  EXPECT_EQ(val2 / val1, UBigInteger<64>(c));
  EXPECT_EQ(val1 / val1, UBigInteger<64>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<64>(1));
}

void division_check2(uint64_t a, uint64_t b) {
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a % b;
  EXPECT_EQ(val1 % val2, UBigInteger<64>(c));
  c = b % a;
  EXPECT_EQ(val2 % val1, UBigInteger<64>(c));
  EXPECT_EQ(val1 % val1, UBigInteger<64>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<64>(0));
}

struct UBigIntegerHeavyTestCase {
  uint64_t a_min;
  uint64_t a_max;
  uint64_t b_min;
  uint64_t b_max;
};

struct UBigIntegerHeavyTest
    : public testing::TestWithParam<UBigIntegerHeavyTestCase> {};

TEST_P(UBigIntegerHeavyTest, heavy_comparison_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      comparison_check(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_addition_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      addition_check(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_substraction_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      substraction_check(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_multiplication_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      multiplication_check(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_division_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      division_check1(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_division_test2) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      division_check2(a, b);
    }
  }
}

static std::vector<UBigIntegerHeavyTestCase> test_cases = {
    {1, 1000, 1, 1000},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     (std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max()},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     1,
     1000},
};

INSTANTIATE_TEST_SUITE_P(UBigIntegerHeavyTestSuite,
                         UBigIntegerHeavyTest,
                         testing::ValuesIn(test_cases));