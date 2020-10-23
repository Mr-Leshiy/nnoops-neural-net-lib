#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

TEST(UBigInteger, comparison_test) {
  UBigInteger val1(431);
  UBigInteger val2(25423);

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

TEST(UBigInteger, addition_substraction_test) {
  UBigInteger val1(66576);
  UBigInteger val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, UBigInteger(120224));

  val1 -= val2;

  EXPECT_EQ(val1, UBigInteger(66576));

  EXPECT_EQ(val1 + val2, UBigInteger(120224));
  EXPECT_EQ(val2 + val1, UBigInteger(120224));

  EXPECT_EQ(val1 - val2, UBigInteger(12928));
  EXPECT_EQ(-(val2 - val1), UBigInteger(12928));

  EXPECT_EQ(val1++, UBigInteger(66576));
  EXPECT_EQ(val1, UBigInteger(66577));

  EXPECT_EQ(++val1, UBigInteger(66578));
  EXPECT_EQ(val1, UBigInteger(66578));

  EXPECT_EQ(val1--, UBigInteger(66578));
  EXPECT_EQ(val1, UBigInteger(66577));

  EXPECT_EQ(--val1, UBigInteger(66576));
  EXPECT_EQ(val1, UBigInteger(66576));

  UBigInteger<8> val3((uint8_t)254);
  EXPECT_EQ(-val3, UBigInteger<8>((uint8_t)2));
  val3 = (uint8_t)3;
  EXPECT_EQ(-val3, UBigInteger<8>((uint8_t)253));

  UBigInteger val4(255);

  EXPECT_EQ(++val4, UBigInteger(256));
  EXPECT_EQ(--val4, UBigInteger(255));
}

TEST(UBigInteger, multiplication_test) {
  UBigInteger val1 = 1234;
  UBigInteger val2 = 4321;

  val1 *= val2;

  EXPECT_EQ(val1, UBigInteger(5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, UBigInteger(5332114));
  EXPECT_EQ(val2 * val1, UBigInteger(5332114));
}

TEST(UBigInteger, toPrettyString_test) {
  UBigInteger<32> val(1234);

  EXPECT_EQ(toPrettyString(val), "4d2");

  val = UBigInteger<32>(1235);

  EXPECT_EQ(toPrettyString(val), "4d3");
}
