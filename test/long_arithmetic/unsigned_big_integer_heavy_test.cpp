#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

template <typename BASE_T>
void comparison_check(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;

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
void addition_check(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  a = (uint32_t)a;
  b = (uint32_t)b;
  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;
  EXPECT_EQ(val1 + val2, UBigIntegerT(a + b));
  EXPECT_EQ(val2 + val1, UBigIntegerT(a + b));
}

template <typename BASE_T>
void substraction_check(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;
  if (a > b) {
    EXPECT_EQ(val1 - val2, UBigIntegerT(a - b));
  } else {
    EXPECT_EQ(val2 - val1, UBigIntegerT(b - a));
  }

  EXPECT_EQ(val1 - val1, UBigIntegerT(0));
  EXPECT_EQ(val2 - val2, UBigIntegerT(0));
}

template <typename BASE_T>
void multiplication_check(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  a = (uint32_t)a;
  b = (uint32_t)b;
  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;
  EXPECT_EQ(val1 * val2, UBigIntegerT(a * b));
  EXPECT_EQ(val2 * val1, UBigIntegerT(a * b));
}

template <typename BASE_T>
void division_check1(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  if (a == 0 || b == 0) {
    return;
  }
  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;
  EXPECT_EQ(val1 / val2, UBigIntegerT(a / b));
  EXPECT_EQ(val2 / val1, UBigIntegerT(b / a));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));
}

template <typename BASE_T>
void division_check2(uint64_t a, uint64_t b) {
  using UBigIntegerT = UBigInteger<64, BASE_T>;

  if (a == 0 || b == 0) {
    return;
  }
  UBigIntegerT val1 = a;
  UBigIntegerT val2 = b;
  EXPECT_EQ(val1 % val2, UBigIntegerT(a % b));
  EXPECT_EQ(val2 % val1, UBigIntegerT(b % a));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));
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
      comparison_check<uint8_t>(a, b);
      comparison_check<uint16_t>(a, b);
      comparison_check<uint32_t>(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_addition_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      addition_check<uint8_t>(a, b);
      addition_check<uint16_t>(a, b);
      addition_check<uint32_t>(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_substraction_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      substraction_check<uint8_t>(a, b);
      substraction_check<uint16_t>(a, b);
      substraction_check<uint32_t>(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_multiplication_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      multiplication_check<uint8_t>(a, b);
      multiplication_check<uint16_t>(a, b);
      multiplication_check<uint32_t>(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_division1_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      division_check1<uint8_t>(a, b);
      division_check1<uint16_t>(a, b);
      division_check1<uint32_t>(a, b);
    }
  }
}

TEST_P(UBigIntegerHeavyTest, heavy_division2_test) {
  auto value = GetParam();
  for (uint64_t a = value.a_min; a < value.a_max; ++a) {
    for (uint64_t b = value.b_min; b < value.b_max; ++b) {
      division_check2<uint8_t>(a, b);
      division_check2<uint16_t>(a, b);
      division_check2<uint32_t>(a, b);
    }
  }
}

static std::vector<UBigIntegerHeavyTestCase> test_cases = {
    {0, 1000, 0, 1000},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     (std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max()},
    {(std::numeric_limits<uint64_t>::max() - 1000),
     std::numeric_limits<uint64_t>::max(),
     0,
     1000},
};

INSTANTIATE_TEST_SUITE_P(UBigIntegerHeavyTestSuite,
                         UBigIntegerHeavyTest,
                         testing::ValuesIn(test_cases));
