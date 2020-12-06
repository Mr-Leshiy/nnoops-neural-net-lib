#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_float.hpp"
using namespace nnoops;

TEST(BigDecimal, multiplication_test) {
  using BigFloatT = BigFloat<1024>;
  BigFloatT val1("3124.3312");
  BigFloatT val2("-12.41551");

  val1 *= val2;

  EXPECT_EQ(val1, BigFloatT("-38790.165256912"));

  val1 = BigFloatT("3124.3312");

  EXPECT_EQ(val1 * val2, BigFloatT("-38790.165256912"));
  EXPECT_EQ(val2 * val1, BigFloatT("-38790.165256912"));

  val2 *= BigFloatT("-1");

  EXPECT_EQ(val1 * val2, BigFloatT("38790.165256912"));
  EXPECT_EQ(val2 * val1, BigFloatT("38790.165256912"));
}

TEST(BigDecimal, toPrettyString_test) {
  BigFloat<> val(1234);

  EXPECT_EQ(toPrettyString(val), "1234*e^(0)");

  val = 1234000000;

  EXPECT_EQ(toPrettyString(val), "1234*e^(6)");

  val = -1234;

  EXPECT_EQ(toPrettyString(val), "-1234*e^(0)");

  val = -1234000000;

  EXPECT_EQ(toPrettyString(val), "-1234*e^(6)");

  val = BigFloat<>("124.2134");

  EXPECT_EQ(toPrettyString(val), "1242134*e^(-4)");

  val = BigFloat<>("-124.2134");

  EXPECT_EQ(toPrettyString(val), "-1242134*e^(-4)");

  val = BigFloat<>("00000.00124");

  EXPECT_EQ(toPrettyString(val), "124*e^(-5)");

  val = BigFloat<>("-0.00124");

  EXPECT_EQ(toPrettyString(val), "-124*e^(-5)");
}
