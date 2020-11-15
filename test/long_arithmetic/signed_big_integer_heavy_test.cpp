#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

void comparison_check(int64_t a, int64_t b) {
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;

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

void addition_check(int64_t a, int64_t b) {
  a = (int32_t)a;
  b = (int32_t)b;
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;
  EXPECT_EQ(val1 + val2, BigInteger<64>(a + b));
  EXPECT_EQ(val2 + val1, BigInteger<64>(a + b));
}

void substraction_check(int64_t a, int64_t b) {
  a = (int32_t)a;
  b = (int32_t)b;
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;
  EXPECT_EQ(val1 - val2, BigInteger<64>(a - b));
  EXPECT_EQ(-(val2 - val1), BigInteger<64>(a - b));

  EXPECT_EQ(val2 - val1, BigInteger<64>(b - a));
  EXPECT_EQ(-(val1 - val2), BigInteger<64>(b - a));

  EXPECT_EQ(val1 - val1, BigInteger<64>(0));
  EXPECT_EQ(val2 - val2, BigInteger<64>(0));
}

void multiplication_check(int64_t a, int64_t b) {
  a = (int32_t)a;
  b = (int32_t)b;
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;
  EXPECT_EQ(val1 * val2, BigInteger<64>(a * b));
  EXPECT_EQ(val2 * val1, BigInteger<64>(a * b));
}

void division_check1(int64_t a, int64_t b) {
  if (a == 0 || b == 0) {
    return;
  }
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;
  EXPECT_EQ(val1 / val2, BigInteger<64>(a / b));
  EXPECT_EQ(val2 / val1, BigInteger<64>(b / a));
  EXPECT_EQ(val1 / val1, BigInteger<64>(1));
  EXPECT_EQ(val2 / val2, BigInteger<64>(1));
}

void division_check2(int64_t a, int64_t b) {
  if (a == 0 || b == 0) {
    return;
  }
  BigInteger<64> val1 = a;
  BigInteger<64> val2 = b;
  EXPECT_EQ(val1 % val2, BigInteger<64>(a % b));
  EXPECT_EQ(val2 % val1, BigInteger<64>(b % a));
  EXPECT_EQ(val1 % val1, BigInteger<64>(0));
  EXPECT_EQ(val2 % val2, BigInteger<64>(0));
}

struct BigIntegerHeavyTestCase {
  int64_t a_min;
  int64_t a_max;
  int64_t b_min;
  int64_t b_max;
};

struct BigIntegerHeavyTest
    : public testing::TestWithParam<BigIntegerHeavyTestCase> {};

TEST_P(BigIntegerHeavyTest, heavy_comparison_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      comparison_check(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_addition_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      addition_check(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_substraction_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      substraction_check(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_multiplication_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      multiplication_check(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_division1_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      division_check1(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_division2_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      division_check2(a, b);
    }
  }
}

static std::vector<BigIntegerHeavyTestCase> test_cases = {
    {-1000, 1000, -1000, 1000},
    {(std::numeric_limits<int64_t>::max() - 1000),
     std::numeric_limits<int64_t>::max(),
     (std::numeric_limits<int64_t>::max() - 1000),
     std::numeric_limits<int64_t>::max()},
    {(std::numeric_limits<int64_t>::max() - 1000),
     std::numeric_limits<int64_t>::max(),
     -1000,
     1000},
    {(std::numeric_limits<int64_t>::min() + 1000),
     std::numeric_limits<int64_t>::min(),
     (std::numeric_limits<int64_t>::min() + 1000),
     std::numeric_limits<int64_t>::min()},
    {(std::numeric_limits<int64_t>::max() - 1000),
     std::numeric_limits<int64_t>::max(),
     (std::numeric_limits<int64_t>::min() + 1000),
     std::numeric_limits<int64_t>::min()},
};

INSTANTIATE_TEST_SUITE_P(BigIntegerHeavyTestSuite,
                         BigIntegerHeavyTest,
                         testing::ValuesIn(test_cases));
