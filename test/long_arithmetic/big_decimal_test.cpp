#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_decimal.hpp"

using namespace nnoops;

TEST(BigDecimal, basic_test) {}

TEST(BigDecimal, toPrettyString_test) {
  BigDecimal<> val(1234);

  EXPECT_EQ(toPrettyString(val), "4d2*e^(4)");

  val = 1234000000;

  EXPECT_EQ(toPrettyString(val), "4d2*e^(a)");

  val = -1234;

  EXPECT_EQ(toPrettyString(val), "-4d2*e^(4)");

  val = -1234000000;

  EXPECT_EQ(toPrettyString(val), "-4d2*e^(a)");

  val = 124.2134;

  EXPECT_EQ(toPrettyString(val), "12f416*e^(3)");

  val = -124.2134;

  EXPECT_EQ(toPrettyString(val), "-12f416*e^(3)");

  val = 0.00124;

  EXPECT_EQ(toPrettyString(val), "7c*e^(-2)");

  val = -0.00124;

  EXPECT_EQ(toPrettyString(val), "-7c*e^(-2)");
}
