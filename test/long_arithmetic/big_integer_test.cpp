#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/big_integer.hpp"

using namespace nnoops;

TEST(BigInteger, basic_test) {
  BigInteger<32> val(-1234);

  EXPECT_EQ(toPrettyString(val), "-000004d2");

  val = BigInteger<32>(1235);

  EXPECT_EQ(toPrettyString(val), "000004d3");
}

TEST(BigInteger, comparison_test) {}
