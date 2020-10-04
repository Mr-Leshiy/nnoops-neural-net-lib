#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_decimal.hpp"

using namespace nnoops;

TEST(BigDecimal, basic_test) {}

TEST(BigDecimal, toPrettyString_test) {
  BigDecimal val(-123.0);
  EXPECT_EQ(toPrettyString(val), "-123.0");

  val = BigDecimal(321);
  EXPECT_EQ(toPrettyString(val), "321.0");
}