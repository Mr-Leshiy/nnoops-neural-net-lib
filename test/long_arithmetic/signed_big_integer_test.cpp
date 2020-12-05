#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

template <uint64_t SIZE, typename BASE_T>
struct BigIntegerTestCase {
  const static uint64_t size = SIZE;
  using base_t = BASE_T;
};

template <typename T>
struct BigIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(BigIntegerTest);

TYPED_TEST_P(BigIntegerTest, comparison_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  BigIntegerT val1(431);
  BigIntegerT val2(25423);

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
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  BigIntegerT val1(66576);
  BigIntegerT val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, BigIntegerT(120224));

  val1 -= val2;

  EXPECT_EQ(val1, BigIntegerT(66576));

  EXPECT_EQ(val1 + val2, BigIntegerT(120224));
  EXPECT_EQ(val1 + val2, BigIntegerT(120224));

  EXPECT_EQ(val1 - val2, BigIntegerT(12928));
  EXPECT_EQ(val2 - val1, BigIntegerT(-12928));

  EXPECT_EQ(val1++, BigIntegerT(66576));
  EXPECT_EQ(val1, BigIntegerT(66577));

  EXPECT_EQ(++val1, BigIntegerT(66578));
  EXPECT_EQ(val1, BigIntegerT(66578));

  EXPECT_EQ(val1--, BigIntegerT(66578));
  EXPECT_EQ(val1, BigIntegerT(66577));

  EXPECT_EQ(--val1, BigIntegerT(66576));
  EXPECT_EQ(val1, BigIntegerT(66576));

  val1 = -12928;

  EXPECT_EQ(val1--, BigIntegerT(-12928));
  EXPECT_EQ(val1, BigIntegerT(-12929));

  EXPECT_EQ(--val1, BigIntegerT(-12930));
  EXPECT_EQ(val1, BigIntegerT(-12930));

  EXPECT_EQ(val1++, BigIntegerT(-12930));
  EXPECT_EQ(val1, BigIntegerT(-12929));

  EXPECT_EQ(++val1, BigIntegerT(-12928));
  EXPECT_EQ(val1, BigIntegerT(-12928));

  val1 += val1;

  EXPECT_EQ(val1, BigIntegerT(-25856));

  val1 -= BigIntegerT(-12928);

  EXPECT_EQ(val1, BigIntegerT(-12928));

  EXPECT_EQ(val1 + val1, BigIntegerT(-25856));
  EXPECT_EQ(val1 - val1, BigIntegerT(0));

  val2 = 12928 * 2;

  EXPECT_EQ(val1 - val2, BigIntegerT(-38784));
  EXPECT_EQ(val1 + val2, BigIntegerT(12928));
}

TYPED_TEST_P(BigIntegerTest, multiplication_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  BigIntegerT val1 = 1234;
  BigIntegerT val2 = -4321;

  val1 *= val2;

  EXPECT_EQ(val1, BigIntegerT(-5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, BigIntegerT(-5332114));
  EXPECT_EQ(val2 * val1, BigIntegerT(-5332114));

  val2 *= -1;

  EXPECT_EQ(val2, BigIntegerT(4321));

  val1 *= val2;

  EXPECT_EQ(val1, BigIntegerT(5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, BigIntegerT(5332114));
  EXPECT_EQ(val2 * val1, BigIntegerT(5332114));

  BigIntegerT val3 = 125;
  BigIntegerT val4 = 2;

  EXPECT_EQ(val3 * val4, BigIntegerT(250));
  EXPECT_EQ(val4 * val3, BigIntegerT(250));

  val3 = 125;
  val4 = -2;

  EXPECT_EQ(val3 * val4, BigIntegerT(-250));
  EXPECT_EQ(val4 * val3, BigIntegerT(-250));

  val3 = -125;
  val4 = 2;

  EXPECT_EQ(val3 * val4, BigIntegerT(-250));
  EXPECT_EQ(val4 * val3, BigIntegerT(-250));

  val3 = -125;
  val4 = -2;

  EXPECT_EQ(val3 * val4, BigIntegerT(250));
  EXPECT_EQ(val4 * val3, BigIntegerT(250));
}

TYPED_TEST_P(BigIntegerTest, division_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  BigIntegerT val1 = 41351;
  BigIntegerT val2 = 5423;

  EXPECT_EQ(val1 / val2, BigIntegerT(7));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(178));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(6726));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(6206255));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, BigIntegerT(3007261));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, BigIntegerT(23774));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, BigIntegerT(1));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 41351;
  val2 = -5423;

  EXPECT_EQ(val1 / val2, BigIntegerT(-7));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 357;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-178));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 13452;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-6726));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 12412511;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-6206255));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 1235984556;
  val2 = -411;

  EXPECT_EQ(val1 / val2, BigIntegerT(-3007261));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 325685126;
  val2 = -13699;

  EXPECT_EQ(val1 / val2, BigIntegerT(-23774));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = 999991;
  val2 = -999990;

  EXPECT_EQ(val1 / val2, BigIntegerT(-1));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -41351;
  val2 = 5423;

  EXPECT_EQ(val1 / val2, BigIntegerT(-7));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-178));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-6726));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, BigIntegerT(-6206255));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, BigIntegerT(-3007261));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, BigIntegerT(-23774));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, BigIntegerT(-1));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -41351;
  val2 = -5423;

  EXPECT_EQ(val1 / val2, BigIntegerT(7));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -357;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(178));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -13452;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(6726));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -12412511;
  val2 = -2;

  EXPECT_EQ(val1 / val2, BigIntegerT(6206255));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -1235984556;
  val2 = -411;

  EXPECT_EQ(val1 / val2, BigIntegerT(3007261));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -325685126;
  val2 = -13699;

  EXPECT_EQ(val1 / val2, BigIntegerT(23774));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));

  val1 = -999991;
  val2 = -999990;

  EXPECT_EQ(val1 / val2, BigIntegerT(1));
  EXPECT_EQ(val2 / val1, BigIntegerT(0));
  EXPECT_EQ(val1 / val1, BigIntegerT(1));
  EXPECT_EQ(val2 / val2, BigIntegerT(1));
}

TYPED_TEST_P(BigIntegerTest, division_test2) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  BigIntegerT val1 = 41351;
  BigIntegerT val2 = 5423;

  EXPECT_EQ(val1 % val2, BigIntegerT(3390));
  EXPECT_EQ(val2 % val1, BigIntegerT(5423));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(0));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, BigIntegerT(285));
  EXPECT_EQ(val2 % val1, BigIntegerT(411));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, BigIntegerT(5100));
  EXPECT_EQ(val2 % val1, BigIntegerT(13699));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(999990));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 41351;
  val2 = -5423;

  EXPECT_EQ(val1 % val2, BigIntegerT(3390));
  EXPECT_EQ(val2 % val1, BigIntegerT(-5423));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 357;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 13452;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(0));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 12412511;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 1235984556;
  val2 = -411;

  EXPECT_EQ(val1 % val2, BigIntegerT(285));
  EXPECT_EQ(val2 % val1, BigIntegerT(-411));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 325685126;
  val2 = -13699;

  EXPECT_EQ(val1 % val2, BigIntegerT(5100));
  EXPECT_EQ(val2 % val1, BigIntegerT(-13699));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = 999991;
  val2 = -999990;

  EXPECT_EQ(val1 % val2, BigIntegerT(1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-999990));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -41351;
  val2 = 5423;

  EXPECT_EQ(val1 % val2, BigIntegerT(-3390));
  EXPECT_EQ(val2 % val1, BigIntegerT(5423));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(0));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, BigIntegerT(-285));
  EXPECT_EQ(val2 % val1, BigIntegerT(411));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, BigIntegerT(-5100));
  EXPECT_EQ(val2 % val1, BigIntegerT(13699));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(999990));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -41351;
  val2 = -5423;

  EXPECT_EQ(val1 % val2, BigIntegerT(-3390));
  EXPECT_EQ(val2 % val1, BigIntegerT(-5423));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -357;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -13452;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(0));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -12412511;
  val2 = -2;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-2));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -1235984556;
  val2 = -411;

  EXPECT_EQ(val1 % val2, BigIntegerT(-285));
  EXPECT_EQ(val2 % val1, BigIntegerT(-411));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -325685126;
  val2 = -13699;

  EXPECT_EQ(val1 % val2, BigIntegerT(-5100));
  EXPECT_EQ(val2 % val1, BigIntegerT(-13699));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));

  val1 = -999991;
  val2 = -999990;

  EXPECT_EQ(val1 % val2, BigIntegerT(-1));
  EXPECT_EQ(val2 % val1, BigIntegerT(-999990));
  EXPECT_EQ(val1 % val1, BigIntegerT(0));
  EXPECT_EQ(val2 % val2, BigIntegerT(0));
}

TYPED_TEST_P(BigIntegerTest, exception_handling_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using BigIntegerT = BigInteger<size, base_t>;

  EXPECT_THROW(BigIntegerT(""), arith_error);

  EXPECT_THROW(BigIntegerT::max_value() + 1, arith_error);
  EXPECT_THROW(1 + BigIntegerT::max_value(), arith_error);
  EXPECT_THROW(++BigIntegerT::max_value(), arith_error);
  EXPECT_THROW(BigIntegerT::max_value()++, arith_error);
  EXPECT_THROW(2 * BigIntegerT::max_value(), arith_error);
  EXPECT_THROW(BigIntegerT::max_value() * 2, arith_error);

  EXPECT_THROW(BigIntegerT::min_value() - 1, arith_error);
  EXPECT_THROW(-(1 - BigIntegerT::min_value()), arith_error);
  EXPECT_THROW(--BigIntegerT::min_value(), arith_error);
  EXPECT_THROW(BigIntegerT::min_value()--, arith_error);
  EXPECT_THROW(2 * BigIntegerT::min_value(), arith_error);
  EXPECT_THROW(BigIntegerT::min_value() * 2, arith_error);
}

REGISTER_TYPED_TEST_SUITE_P(BigIntegerTest,
                            comparison_test,
                            addition_substraction_test,
                            multiplication_test,
                            division_test,
                            division_test2,
                            exception_handling_test);

typedef ::testing::Types<BigIntegerTestCase<64, uint8_t>,
                         BigIntegerTestCase<128, uint8_t>,
                         BigIntegerTestCase<256, uint8_t>,
                         BigIntegerTestCase<512, uint8_t>,
                         BigIntegerTestCase<1024, uint8_t>,
                         BigIntegerTestCase<2048, uint8_t>,
                         BigIntegerTestCase<4096, uint8_t>,
                         BigIntegerTestCase<64, uint16_t>,
                         BigIntegerTestCase<128, uint16_t>,
                         BigIntegerTestCase<256, uint16_t>,
                         BigIntegerTestCase<512, uint16_t>,
                         BigIntegerTestCase<1024, uint16_t>,
                         BigIntegerTestCase<2048, uint16_t>,
                         BigIntegerTestCase<4096, uint16_t>,
                         BigIntegerTestCase<64, uint32_t>,
                         BigIntegerTestCase<128, uint32_t>,
                         BigIntegerTestCase<256, uint32_t>,
                         BigIntegerTestCase<512, uint32_t>,
                         BigIntegerTestCase<1024, uint32_t>,
                         BigIntegerTestCase<2048, uint32_t>,
                         BigIntegerTestCase<4096, uint32_t>>
    BigIntegerTestCases;

INSTANTIATE_TYPED_TEST_SUITE_P(BigIntegerTestSuite,
                               BigIntegerTest,
                               BigIntegerTestCases);

TEST(BigInteger, toPrettyString_test) {
  BigInteger<> val(1234);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d2");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1234");

  val = -1235;

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "-4d3");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "-1235");

  val = BigInteger<>("4d2", NumFormat::HEX);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d2");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1234");

  val = BigInteger<>("-1235", NumFormat::DEC);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "-4d3");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "-1235");
}

TEST(BigInteger, basic_values_test) {
  EXPECT_EQ(toPrettyString(BigInteger<32>::max_value(), NumFormat::HEX),
            "ffffffff");
  EXPECT_EQ(toPrettyString(BigInteger<32>::zero_value(), NumFormat::HEX), "0");
  EXPECT_EQ(toPrettyString(BigInteger<32>::min_value(), NumFormat::HEX),
            "-ffffffff");

  EXPECT_EQ(toPrettyString(BigInteger<64>::max_value(), NumFormat::HEX),
            "ffffffffffffffff");
  EXPECT_EQ(toPrettyString(BigInteger<64>::zero_value(), NumFormat::HEX), "0");
  EXPECT_EQ(toPrettyString(BigInteger<64>::min_value(), NumFormat::HEX),
            "-ffffffffffffffff");

  EXPECT_EQ(toPrettyString(BigInteger<32>::max_value(), NumFormat::DEC),
            "4294967295");
  EXPECT_EQ(toPrettyString(BigInteger<32>::zero_value(), NumFormat::DEC), "0");
  EXPECT_EQ(toPrettyString(BigInteger<32>::min_value(), NumFormat::DEC),
            "-4294967295");

  EXPECT_EQ(toPrettyString(BigInteger<64>::max_value(), NumFormat::DEC),
            "18446744073709551615");
  EXPECT_EQ(toPrettyString(BigInteger<64>::zero_value(), NumFormat::DEC), "0");
  EXPECT_EQ(toPrettyString(BigInteger<64>::min_value(), NumFormat::DEC),
            "-18446744073709551615");
}
