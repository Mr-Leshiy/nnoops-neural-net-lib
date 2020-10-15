#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/big_integer.hpp"

using namespace nnoops;

TEST(BigInteger, comparison_test) {
  BigInteger val1(-1234);
  BigInteger val2(1234);

  EXPECT_TRUE(val1 == val1);
  EXPECT_FALSE(val1 == val2);
  EXPECT_FALSE(val1 != val1);
  EXPECT_TRUE(val1 != val2);

  EXPECT_TRUE(val1 < val2);
  EXPECT_FALSE(val2 < val1);
  EXPECT_FALSE(val1 < val1);
  EXPECT_FALSE(val2 < val2);

  EXPECT_FALSE(val1 > val2);
  EXPECT_TRUE(val2 > val1);
  EXPECT_FALSE(val1 > val1);
  EXPECT_FALSE(val2 > val2);

  EXPECT_TRUE(val1 <= val2);
  EXPECT_FALSE(val2 <= val1);
  EXPECT_TRUE(val1 <= val1);
  EXPECT_TRUE(val2 <= val2);

  EXPECT_FALSE(val1 >= val2);
  EXPECT_TRUE(val2 >= val1);
  EXPECT_TRUE(val1 >= val1);
  EXPECT_TRUE(val2 >= val2);
}

TEST(BigInteger, addition_test) {
  BigInteger val1(-1234);
  BigInteger val2(1234);

  BigInteger res;

  res = val1 + val1;

  EXPECT_EQ(toPrettyString(res), toPrettyString(BigInteger(-2468)));

  res += 1234;

  EXPECT_EQ(toPrettyString(res), toPrettyString(BigInteger(-1234)));

}

TEST(BigInteger, toPrettyString_test) {
  BigInteger<32> val(-1234);

  EXPECT_EQ(toPrettyString(val), "-000004d2");

  val = BigInteger<32>(1235);

  EXPECT_EQ(toPrettyString(val), "000004d3");
}
