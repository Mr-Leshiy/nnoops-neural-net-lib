#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_decimal.hpp"

using namespace nnoops;

TEST(BigDecimal, basic_test) {}

TEST(BigDecimal, toPrettyString_test) {
  BigDecimal val(5, 6);
  EXPECT_EQ(toPrettyString(val), "5/6");
}
