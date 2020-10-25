#include <gtest/gtest.h>

#include <limits>

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

  UBigInteger<8> val3 = (uint8_t)125;
  UBigInteger<8> val4 = (uint8_t)2;

  EXPECT_EQ(val3 * val4, UBigInteger<8>((uint8_t)250));
  EXPECT_EQ(val4 * val3, UBigInteger<8>((uint8_t)250));

  val4++;

  EXPECT_EQ(val3 * val4, UBigInteger<8>((uint8_t)119));
  EXPECT_EQ(val4 * val3, UBigInteger<8>((uint8_t)119));

  val4 = (uint8_t)125;

  EXPECT_EQ(val3 * val4, UBigInteger<8>((uint8_t)9));
  EXPECT_EQ(val4 * val3, UBigInteger<8>((uint8_t)9));
}

TEST(UBigInteger, division_test) {
  UBigInteger val1 = 41351;
  UBigInteger val2 = 5423;

  EXPECT_EQ(val1 / val2, UBigInteger(7));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger(178));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger(6726));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger(6206255));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  val1 = 121458741574;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger(60729370787));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  val1 = 16156165131561652;
  val2 = 6553614;

  EXPECT_EQ(val1 / val2, UBigInteger(2465229891));
  EXPECT_EQ(val2 / val1, UBigInteger(0));

  EXPECT_EQ(val1 / val1, UBigInteger(1));
  EXPECT_EQ(val2 / val2, UBigInteger(1));

  val1 = 123;
  val2 = 12;
  val2 = -val2;

  EXPECT_EQ(val1 / val1, UBigInteger(1));
  EXPECT_EQ(val2 / val2, UBigInteger(1));
}

TEST(UBigInteger, division_test2) {
  UBigInteger val1 = 41351;
  UBigInteger val2 = 5423;

  EXPECT_EQ(val1 % val2, UBigInteger(3390));
  EXPECT_EQ(val2 % val1, UBigInteger(5423));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger(1));
  EXPECT_EQ(val2 % val1, UBigInteger(2));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger(0));
  EXPECT_EQ(val2 % val1, UBigInteger(2));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger(1));
  EXPECT_EQ(val2 % val1, UBigInteger(2));

  val1 = 121458741574;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger(0));
  EXPECT_EQ(val2 % val1, UBigInteger(2));

  val1 = 16156165131561652;
  val2 = 6553614;

  EXPECT_EQ(val1 % val2, UBigInteger(4685578));
  EXPECT_EQ(val2 % val1, UBigInteger(6553614));

  EXPECT_EQ(val1 % val1, UBigInteger(0));
  EXPECT_EQ(val2 % val2, UBigInteger(0));

  val1 = 123;
  val2 = 12;
  val2 = -val2;

  EXPECT_EQ(val1 % val1, UBigInteger(0));
  EXPECT_EQ(val2 % val2, UBigInteger(0));
}

TEST(UBigInteger, toPrettyString_test) {
  UBigInteger<32> val(1234);

  EXPECT_EQ(toPrettyString(val), "4d2");

  val = UBigInteger<32>(1235);

  EXPECT_EQ(toPrettyString(val), "4d3");
}
