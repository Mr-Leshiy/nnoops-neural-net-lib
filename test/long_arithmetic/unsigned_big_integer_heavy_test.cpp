#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

void comparison_check(uint64_t a, uint64_t b) {
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;

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
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;
  EXPECT_EQ(val1 + val2, UBigInteger<128>(a + b));
  EXPECT_EQ(val2 + val1, UBigInteger<128>(a + b));
}

void substraction_check(uint64_t a, uint64_t b) {
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;
  if (a > b) {
    EXPECT_EQ(val1 - val2, UBigInteger<128>(a - b));
  } else {
    EXPECT_EQ(val2 - val1, UBigInteger<128>(b - a));
  }

  EXPECT_EQ(val1 - val1, UBigInteger<128>(0));
  EXPECT_EQ(val2 - val2, UBigInteger<128>(0));
}

void multiplication_check(uint64_t a, uint64_t b) {
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;
  EXPECT_EQ(val1 * val2, UBigInteger<128>(a * b));
  EXPECT_EQ(val2 * val1, UBigInteger<128>(a * b));
}

void division_check1(uint64_t a, uint64_t b) {
  if (a == 0 || b == 0) {
    return;
  }
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;
  EXPECT_EQ(val1 / val2, UBigInteger<128>(a / b));
  EXPECT_EQ(val2 / val1, UBigInteger<128>(b / a));
  EXPECT_EQ(val1 / val1, UBigInteger<128>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<128>(1));
}

void division_check2(uint64_t a, uint64_t b) {
  if (a == 0 || b == 0) {
    return;
  }
  UBigInteger<128> val1 = a;
  UBigInteger<128> val2 = b;
  EXPECT_EQ(val1 % val2, UBigInteger<128>(a % b));
  EXPECT_EQ(val2 % val1, UBigInteger<128>(b % a));
  EXPECT_EQ(val1 % val1, UBigInteger<128>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<128>(0));
}

struct UBigIntegerHeavyTestCase {
  uint64_t a_min;
  uint64_t a_max;
  uint64_t b_min;
  uint64_t b_max;
};

struct UBigIntegerHeavyTest
    : public testing::TestWithParam<UBigIntegerHeavyTestCase> {};

TEST_P(UBigIntegerHeavyTest, heavy_complex_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      comparison_check(a, b);
      addition_check(a, b);
      substraction_check(a, b);
      multiplication_check(a, b);
      division_check1(a, b);
      division_check2(a, b);
    }
  }
}

static std::vector<UBigIntegerHeavyTestCase> test_cases = {
    /*{0, 1000, 0, 1000},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     (std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max()},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     0,
     1000}, */
};

INSTANTIATE_TEST_SUITE_P(UBigIntegerHeavyTestSuite,
                         UBigIntegerHeavyTest,
                         testing::ValuesIn(test_cases));