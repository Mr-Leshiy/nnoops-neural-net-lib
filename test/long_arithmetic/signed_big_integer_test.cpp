#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

template <uint64_t SIZE>
struct BigIntegerTestCase {
  const static uint64_t size = SIZE;
};

template <typename T>
struct BigIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(BigIntegerTest);
TYPED_TEST_P(BigIntegerTest, comparison_test) {
  const static uint64_t size = TypeParam::size;
  BigInteger<size> val1(431);
  BigInteger<size> val2(25423);

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

TYPED_TEST_P(BigIntegerTest, addition_substraction_test) {
  const static uint64_t size = TypeParam::size;
  BigInteger<size> val1(66576);
  BigInteger<size> val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, BigInteger<size>(120224));

  val1 -= val2;

  EXPECT_EQ(val1, BigInteger<size>(66576));

  EXPECT_EQ(val1 + val2, BigInteger<size>(120224));
  EXPECT_EQ(val1 + val2, BigInteger<size>(120224));

  EXPECT_EQ(val1 - val2, BigInteger<size>(12928));
  EXPECT_EQ(val2 - val1, BigInteger<size>(-12928));

  EXPECT_EQ(val1++, BigInteger<size>(66576));
  EXPECT_EQ(val1, BigInteger<size>(66577));

  EXPECT_EQ(++val1, BigInteger<size>(66578));
  EXPECT_EQ(val1, BigInteger<size>(66578));

  EXPECT_EQ(val1--, BigInteger<size>(66578));
  EXPECT_EQ(val1, BigInteger<size>(66577));

  EXPECT_EQ(--val1, BigInteger<size>(66576));
  EXPECT_EQ(val1, BigInteger<size>(66576));

  val1 = -12928;

  EXPECT_EQ(val1--, BigInteger<size>(-12928));
  EXPECT_EQ(val1, BigInteger<size>(-12929));

  EXPECT_EQ(--val1, BigInteger<size>(-12930));
  EXPECT_EQ(val1, BigInteger<size>(-12930));

  EXPECT_EQ(val1++, BigInteger<size>(-12930));
  EXPECT_EQ(val1, BigInteger<size>(-12929));

  EXPECT_EQ(++val1, BigInteger<size>(-12928));
  EXPECT_EQ(val1, BigInteger<size>(-12928));

  val1 += val1;

  EXPECT_EQ(val1, BigInteger<size>(-25856));

  val1 -= BigInteger<size>(-12928);

  EXPECT_EQ(val1, BigInteger<size>(-12928));

  EXPECT_EQ(val1 + val1, BigInteger<size>(-25856));
  EXPECT_EQ(val1 - val1, BigInteger<size>(0));

  val2 = 12928 * 2;

  EXPECT_EQ(val1 - val2, BigInteger<size>(-38784));
  EXPECT_EQ(val1 + val2, BigInteger<size>(12928));
}

TYPED_TEST_P(BigIntegerTest, multiplication_test) {
  const static uint64_t size = TypeParam::size;
  BigInteger<size> val1 = 1234;
  BigInteger<size> val2 = -4321;

  val1 *= val2;

  EXPECT_EQ(val1, BigInteger<size>(-5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, BigInteger<size>(-5332114));
  EXPECT_EQ(val2 * val1, BigInteger<size>(-5332114));

  val2 *= -1;
  val1 = 1234;

  EXPECT_EQ(val2, BigInteger<size>(4321));

  val1 *= val2;

  EXPECT_EQ(val1, BigInteger<size>(5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, BigInteger<size>(5332114));
  EXPECT_EQ(val2 * val1, BigInteger<size>(5332114));

  BigInteger<size> val3 = 125;
  BigInteger<size> val4 = 2;

  EXPECT_EQ(val3 * val4, BigInteger<size>(250));
  EXPECT_EQ(val4 * val3, BigInteger<size>(250));

  val3 = 125;
  val4 = -2;

  EXPECT_EQ(val3 * val4, BigInteger<size>(-250));
  EXPECT_EQ(val4 * val3, BigInteger<size>(-250));

  val3 = -125;
  val4 = 2;

  EXPECT_EQ(val3 * val4, BigInteger<size>(-250));
  EXPECT_EQ(val4 * val3, BigInteger<size>(-250));

  val3 = -125;
  val4 = -2;

  EXPECT_EQ(val3 * val4, BigInteger<size>(250));
  EXPECT_EQ(val4 * val3, BigInteger<size>(250));
}

TYPED_TEST_P(BigIntegerTest, division_test) {
  const static uint64_t size = TypeParam::size;
  BigInteger<size> val1 = 41351;
  BigInteger<size> val2 = 5423;

  EXPECT_EQ(val1 / val2, BigInteger<size>(7));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(178));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(6726));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(6206255));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, BigInteger<size>(3007261));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, BigInteger<size>(23774));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, BigInteger<size>(1));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 41351;
  val2 = -5423;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-7));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 357;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-178));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 13452;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-6726));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 12412511;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-6206255));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 1235984556;
  val2 = -411;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-3007261));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 325685126;
  val2 = -13699;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-23774));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = 999991;
  val2 = -999990;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -41351;
  val2 = 5423;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-7));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-178));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-6726));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-6206255));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-3007261));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-23774));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -41351;
  val2 = -5423;

  EXPECT_EQ(val1 / val2, BigInteger<size>(7));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -357;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(178));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -13452;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(6726));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -12412511;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigInteger<size>(6206255));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -1235984556;
  val2 = -411;

  EXPECT_EQ(val1 / val2, BigInteger<size>(3007261));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -325685126;
  val2 = -13699;

  EXPECT_EQ(val1 / val2, BigInteger<size>(23774));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));

  val1 = -999991;
  val2 = -999990;

  EXPECT_EQ(val1 / val2, BigInteger<size>(1));
  EXPECT_EQ(val2 / val1, BigInteger<size>(0));
  EXPECT_EQ(val1 / val1, BigInteger<size>(1));
  EXPECT_EQ(val2 / val2, BigInteger<size>(1));
}

TYPED_TEST_P(BigIntegerTest, division_test2) {
  const static uint64_t size = TypeParam::size;
  BigInteger<size> val1 = 41351;
  BigInteger<size> val2 = 5423;

  EXPECT_EQ(val1 % val2, BigInteger<size>(3390));
  EXPECT_EQ(val2 % val1, BigInteger<size>(5423));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(0));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, BigInteger<size>(285));
  EXPECT_EQ(val2 % val1, BigInteger<size>(411));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, BigInteger<size>(5100));
  EXPECT_EQ(val2 % val1, BigInteger<size>(13699));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(999990));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 41351;
  val2 = -5423;

  EXPECT_EQ(val1 % val2, BigInteger<size>(3390));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-5423));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 357;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 13452;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(0));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 12412511;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 1235984556;
  val2 = -411;

  EXPECT_EQ(val1 % val2, BigInteger<size>(285));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-411));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 325685126;
  val2 = -13699;

  EXPECT_EQ(val1 % val2, BigInteger<size>(5100));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-13699));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = 999991;
  val2 = -999990;

  EXPECT_EQ(val1 % val2, BigInteger<size>(1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-999990));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -41351;
  val2 = 5423;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-3390));
  EXPECT_EQ(val2 % val1, BigInteger<size>(5423));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(0));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-285));
  EXPECT_EQ(val2 % val1, BigInteger<size>(411));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-5100));
  EXPECT_EQ(val2 % val1, BigInteger<size>(13699));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(999990));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -41351;
  val2 = -5423;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-3390));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-5423));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -357;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -13452;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(0));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -12412511;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-2));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -1235984556;
  val2 = -411;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-285));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-411));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -325685126;
  val2 = -13699;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-5100));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-13699));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));

  val1 = -999991;
  val2 = -999990;

  EXPECT_EQ(val1 % val2, BigInteger<size>(-1));
  EXPECT_EQ(val2 % val1, BigInteger<size>(-999990));
  EXPECT_EQ(val1 % val1, BigInteger<size>(0));
  EXPECT_EQ(val2 % val2, BigInteger<size>(0));
}

TYPED_TEST_P(BigIntegerTest, exception_handling_test) {
  const static uint64_t size = TypeParam::size;

  EXPECT_THROW(BigInteger<size>::max_value() + 1, arith_error);
  EXPECT_THROW(1 + BigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(++BigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(BigInteger<size>::max_value()++, arith_error);
  EXPECT_THROW(2 * BigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(BigInteger<size>::max_value() * 2, arith_error);

  EXPECT_THROW(BigInteger<size>::min_value() - 1, arith_error);
  EXPECT_THROW(-(1 - BigInteger<size>::min_value()), arith_error);
  EXPECT_THROW(--BigInteger<size>::min_value(), arith_error);
  EXPECT_THROW(BigInteger<size>::min_value()--, arith_error);
  EXPECT_THROW(2 * BigInteger<size>::min_value(), arith_error);
  EXPECT_THROW(BigInteger<size>::min_value() * 2, arith_error);
}

REGISTER_TYPED_TEST_SUITE_P(BigIntegerTest,
                            comparison_test,
                            addition_substraction_test,
                            multiplication_test,
                            division_test,
                            division_test2,
                            exception_handling_test);

typedef ::testing::Types<BigIntegerTestCase<64>,
                         BigIntegerTestCase<128>,
                         BigIntegerTestCase<256>,
                         BigIntegerTestCase<512>,
                         BigIntegerTestCase<1024>,
                         BigIntegerTestCase<2048>,
                         BigIntegerTestCase<4096>>
    BigIntegerTestCases;

INSTANTIATE_TYPED_TEST_SUITE_P(BigIntegerTestSuite,
                               BigIntegerTest,
                               BigIntegerTestCases);

TEST(BigInteger, toPrettyString_test) {
  BigInteger<32> val(1234);

  EXPECT_EQ(toPrettyString(val), "4d2");

  val = -1235;

  EXPECT_EQ(toPrettyString(val), "-4d3");
}

TEST(BigInteger, basic_values_test) {
  EXPECT_EQ(toPrettyString(BigInteger<32>::max_value()), "ffffffff");
  EXPECT_EQ(toPrettyString(BigInteger<32>::zero_value()), "0");
  EXPECT_EQ(toPrettyString(BigInteger<32>::min_value()), "-ffffffff");

  EXPECT_EQ(toPrettyString(BigInteger<64>::max_value()), "ffffffffffffffff");
  EXPECT_EQ(toPrettyString(BigInteger<64>::zero_value()), "0");
  EXPECT_EQ(toPrettyString(BigInteger<64>::min_value()), "-ffffffffffffffff");
}
