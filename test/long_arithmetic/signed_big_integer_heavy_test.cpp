#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

template <typename BASE_T>
void comparison_check(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  BigIntegerT val1 = a;
  BigIntegerT val2 = b;

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

template <typename BASE_T>
void addition_check(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  a = (int32_t)a;
  b = (int32_t)b;
  BigIntegerT val1 = a;
  BigIntegerT val2 = b;
  EXPECT_EQ(val1 + val2, BigIntegerT(a + b));
  EXPECT_EQ(val2 + val1, BigIntegerT(a + b));
}

template <typename BASE_T>
void substraction_check(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  a = (int32_t)a;
  b = (int32_t)b;
  BigIntegerT val1 = a;
  BigIntegerT val2 = b;
  EXPECT_EQ(val1 - val2, BigIntegerT(a - b));
  EXPECT_EQ(-(val2 - val1), BigIntegerT(a - b));

  EXPECT_EQ(val2 - val1, BigIntegerT(b - a));
  EXPECT_EQ(-(val1 - val2), BigIntegerT(b - a));

  EXPECT_EQ(val1 - val1, BigIntegerT(0));
  EXPECT_EQ(val2 - val2, BigIntegerT(0));
}

template <typename BASE_T>
void multiplication_check(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  a = (int32_t)a;
  b = (int32_t)b;
  BigIntegerT val1 = a;
  BigIntegerT val2 = b;
  EXPECT_EQ(val1 * val2, BigIntegerT(a * b));
  EXPECT_EQ(val2 * val1, BigIntegerT(a * b));
}

template <typename BASE_T>
void division_check1(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  if (a == 0 || b == 0) {
    return;
  }
  BigIntegerT val1 = a;
  BigIntegerT val2 = b;
  EXPECT_EQ(val1 / val2, BigIntegerT(a / b));
  EXPECT_EQ(val2 / val1, BigIntegerT(b / a));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));
}

template <typename BASE_T>
void division_check2(int64_t a, int64_t b) {
  using BigIntegerT = BigInteger<64, BASE_T>;

  if (a == 0 || b == 0) {
    return;
  }
  BigIntegerT val1 = a;
  BigIntegerT val2 = b;
  EXPECT_EQ(val1 % val2, BigIntegerT(a % b));
  EXPECT_EQ(val2 % val1, BigIntegerT(b % a));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));
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
      comparison_check<uint8_t>(a, b);
      comparison_check<uint16_t>(a, b);
      comparison_check<uint32_t>(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_addition_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      addition_check<uint8_t>(a, b);
      addition_check<uint16_t>(a, b);
      addition_check<uint32_t>(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_substraction_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      substraction_check<uint8_t>(a, b);
      substraction_check<uint16_t>(a, b);
      substraction_check<uint32_t>(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_multiplication_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      multiplication_check<uint8_t>(a, b);
      multiplication_check<uint16_t>(a, b);
      multiplication_check<uint32_t>(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_division1_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      division_check1<uint8_t>(a, b);
      division_check1<uint16_t>(a, b);
      division_check1<uint32_t>(a, b);
    }
  }
}

TEST_P(BigIntegerHeavyTest, heavy_division2_test) {
  auto value = GetParam();
  for (int64_t a = value.a_min; a < value.a_max; ++a) {
    for (int64_t b = value.b_min; b < value.b_max; ++b) {
      division_check2<uint8_t>(a, b);
      division_check2<uint16_t>(a, b);
      division_check2<uint32_t>(a, b);
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
