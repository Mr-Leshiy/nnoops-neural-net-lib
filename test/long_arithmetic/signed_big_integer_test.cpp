#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

TEST(BigInteger, comparison_test) {
  BigInteger val1(431);
  BigInteger val2(25423);

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

  val1 = -431;
  val2 = 431;

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

  val1 = -25423;
  val2 = -431;

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

TEST(BigInteger, addition_substraction_test) {
  BigInteger val1(66576);
  BigInteger val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, BigInteger(120224));

  val1 -= val2;

  EXPECT_EQ(val1, BigInteger(66576));

  EXPECT_EQ(val1 + val2, BigInteger(120224));
  EXPECT_EQ(val1 + val2, BigInteger(120224));

  EXPECT_EQ(val1 - val2, BigInteger(12928));
  EXPECT_EQ(val2 - val1, BigInteger(-12928));

  EXPECT_EQ(val1++, BigInteger(66576));
  EXPECT_EQ(val1, BigInteger(66577));

  EXPECT_EQ(++val1, BigInteger(66578));
  EXPECT_EQ(val1, BigInteger(66578));

  EXPECT_EQ(val1--, BigInteger(66578));
  EXPECT_EQ(val1, BigInteger(66577));

  EXPECT_EQ(--val1, BigInteger(66576));
  EXPECT_EQ(val1, BigInteger(66576));

  val1 = -12928;

  EXPECT_EQ(val1--, BigInteger(-12928));
  EXPECT_EQ(val1, BigInteger(-12929));

  EXPECT_EQ(--val1, BigInteger(-12930));
  EXPECT_EQ(val1, BigInteger(-12930));

  EXPECT_EQ(val1++, BigInteger(-12930));
  EXPECT_EQ(val1, BigInteger(-12929));

  EXPECT_EQ(++val1, BigInteger(-12928));
  EXPECT_EQ(val1, BigInteger(-12928));

  val1 += val1;

  EXPECT_EQ(val1, BigInteger(-25856));

  val1 -= BigInteger(-12928);

  EXPECT_EQ(val1, BigInteger(-12928));

  EXPECT_EQ(val1 + val1, BigInteger(-25856));
  EXPECT_EQ(val1 - val1, BigInteger(0));

  val2 = 12928 * 2;

  EXPECT_EQ(val1 - val2, BigInteger(-38784));
  EXPECT_EQ(val1 + val2, BigInteger(12928));
}

TEST(BigInteger, multiplication_test) {}

TEST(BigInteger, division_test) {}

TEST(BigInteger, division_test2) {}

TEST(BigInteger, toPrettyString_test) {
  BigInteger val(1234);

  EXPECT_EQ(toPrettyString(val), "00000000000004d2");

  val = -1235;

  EXPECT_EQ(toPrettyString(val), "-00000000000004d3");
}

TEST(BigInteger, basic_values_test) {
  BigInteger<64> val1 = BigInteger<64>::max_value();
  EXPECT_EQ(toPrettyString(val1), "ffffffffffffffff");
  val1 = BigInteger<64>::zero_value();
  EXPECT_EQ(toPrettyString(val1), "0000000000000000");
  val1 = BigInteger<64>::min_value();
  EXPECT_EQ(toPrettyString(val1), "-ffffffffffffffff");

  BigInteger<128> val2 = BigInteger<128>::max_value();
  EXPECT_EQ(toPrettyString(val2), "ffffffffffffffffffffffffffffffff");
  val2 = BigInteger<128>::zero_value();
  EXPECT_EQ(toPrettyString(val2), "00000000000000000000000000000000");
  val2 = BigInteger<128>::min_value();
  EXPECT_EQ(toPrettyString(val2), "-ffffffffffffffffffffffffffffffff");

  BigInteger<256> val3 = BigInteger<256>::max_value();
  EXPECT_EQ(toPrettyString(val3),
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
  val3 = BigInteger<256>::zero_value();
  EXPECT_EQ(toPrettyString(val3),
            "0000000000000000000000000000000000000000000000000000000000000000");
  val3 = BigInteger<256>::min_value();
  EXPECT_EQ(
      toPrettyString(val3),
      "-ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
}
