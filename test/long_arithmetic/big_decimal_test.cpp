#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_decimal.hpp"

using namespace nnoops;

TEST(BigDecimal, basic_test) {}

TEST(BigDecimal, toPrettyString_test) {
  BigDecimal val(-123.123);
  EXPECT_EQ(toPrettyString(val), "-123.123000");

  val = BigDecimal(321.2134);
  EXPECT_EQ(toPrettyString(val), "321.213400");

  val = BigDecimal("-21.412");
  EXPECT_EQ(toPrettyString(val), "-21.412");

  val = BigDecimal(".412");
  EXPECT_EQ(toPrettyString(val), "0.412");

  val = BigDecimal("-.412");
  EXPECT_EQ(toPrettyString(val), "-0.412");
}