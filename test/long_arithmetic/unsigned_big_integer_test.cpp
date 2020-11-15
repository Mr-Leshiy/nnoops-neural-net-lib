#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

template <uint64_t SIZE>
struct UBigIntegerTestCase {
  const static uint64_t size = SIZE;
};

template <typename T>
struct UBigIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(UBigIntegerTest);

TYPED_TEST_P(UBigIntegerTest, comparison_test) {
  const static uint64_t size = TypeParam::size;
  UBigInteger<size> val1(431);
  UBigInteger<size> val2(25423);

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

TYPED_TEST_P(UBigIntegerTest, addition_substraction_test) {
  const static uint64_t size = TypeParam::size;
  UBigInteger<size> val1(66576);
  UBigInteger<size> val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, UBigInteger<size>(120224));

  val1 -= val2;

  EXPECT_EQ(val1, UBigInteger<size>(66576));

  EXPECT_EQ(val1 + val2, UBigInteger<size>(120224));
  EXPECT_EQ(val2 + val1, UBigInteger<size>(120224));

  EXPECT_EQ(val1 - val2, UBigInteger<size>(12928));

  EXPECT_EQ(val1++, UBigInteger<size>(66576));
  EXPECT_EQ(val1, UBigInteger<size>(66577));

  EXPECT_EQ(++val1, UBigInteger<size>(66578));
  EXPECT_EQ(val1, UBigInteger<size>(66578));

  EXPECT_EQ(val1--, UBigInteger<size>(66578));
  EXPECT_EQ(val1, UBigInteger<size>(66577));

  EXPECT_EQ(--val1, UBigInteger<size>(66576));
  EXPECT_EQ(val1, UBigInteger<size>(66576));

  UBigInteger<size> val5(255);

  EXPECT_EQ(++val5, UBigInteger<size>(256));
  EXPECT_EQ(--val5, UBigInteger<size>(255));
}

TYPED_TEST_P(UBigIntegerTest, multiplication_test) {
  const static uint64_t size = TypeParam::size;
  UBigInteger<size> val1 = 1234;
  UBigInteger<size> val2 = 4321;

  val1 *= val2;

  EXPECT_EQ(val1, UBigInteger<size>(5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, UBigInteger<size>(5332114));
  EXPECT_EQ(val2 * val1, UBigInteger<size>(5332114));

  UBigInteger<size> val3 = 125;
  UBigInteger<size> val4 = 2;

  EXPECT_EQ(val3 * val4, UBigInteger<size>(250));
  EXPECT_EQ(val4 * val3, UBigInteger<size>(250));
}

TYPED_TEST_P(UBigIntegerTest, division_test) {
  const static uint64_t size = TypeParam::size;
  UBigInteger<size> val1 = 41351;
  UBigInteger<size> val2 = 5423;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(7));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(178));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(6726));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(6206255));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(3007261));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(23774));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val1, UBigInteger<size>(0));
  EXPECT_EQ(val1 / val1, UBigInteger<size>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<size>(1));
}

TYPED_TEST_P(UBigIntegerTest, division_test2) {
  const static uint64_t size = TypeParam::size;
  UBigInteger<size> val1 = 41351;
  UBigInteger<size> val2 = 5423;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(3390));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(5423));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(1));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(2));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(2));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(1));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(2));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(285));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(411));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(5100));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(13699));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, UBigInteger<size>(1));
  EXPECT_EQ(val2 % val1, UBigInteger<size>(999990));
  EXPECT_EQ(val1 % val1, UBigInteger<size>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<size>(0));
}

TYPED_TEST_P(UBigIntegerTest, exception_handling_test) {
  const static uint64_t size = TypeParam::size;
  EXPECT_THROW(UBigInteger<size> tmp(-12), arith_error);

  EXPECT_THROW(UBigInteger<size>::max_value() + 1, arith_error);
  EXPECT_THROW(1 + UBigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(++UBigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(UBigInteger<size>::max_value()++, arith_error);
  EXPECT_THROW(2 * UBigInteger<size>::max_value(), arith_error);
  EXPECT_THROW(UBigInteger<size>::max_value() * 2, arith_error);

  EXPECT_THROW(UBigInteger<size>::min_value() - 1, arith_error);
  EXPECT_THROW(--UBigInteger<size>::min_value(), arith_error);
  EXPECT_THROW(UBigInteger<size>::min_value()--, arith_error);
}

REGISTER_TYPED_TEST_SUITE_P(UBigIntegerTest,
                            comparison_test,
                            addition_substraction_test,
                            multiplication_test,
                            division_test,
                            division_test2,
                            exception_handling_test);

typedef ::testing::Types<UBigIntegerTestCase<64>,
                         UBigIntegerTestCase<128>,
                         UBigIntegerTestCase<256>,
                         UBigIntegerTestCase<512>,
                         UBigIntegerTestCase<1024>,
                         UBigIntegerTestCase<2048>,
                         UBigIntegerTestCase<4096>>
    UBigIntegerTestCases;

INSTANTIATE_TYPED_TEST_SUITE_P(UBigIntegerTestSuite,
                               UBigIntegerTest,
                               UBigIntegerTestCases);

TEST(UBigInteger, small_multiplication_test) {}

TEST(UBigInteger, small_addition_substraction_test) {}

TEST(UBigInteger, small_division_test) {}

TEST(UBigInteger, small_division_test2) {}

TEST(UBigInteger, toPrettyString_test) {
  UBigInteger<32> val(1234);

  EXPECT_EQ(toPrettyString(val), "000004d2");

  val = 1235;

  EXPECT_EQ(toPrettyString(val), "000004d3");
}

TEST(UBigInteger, basic_values_test) {
  UBigInteger<8> val1 = UBigInteger<8>::max_value();
  EXPECT_EQ(toPrettyString(val1), "ff");
  val1 = UBigInteger<8>::zero_value();
  EXPECT_EQ(toPrettyString(val1), "00");
  val1 = UBigInteger<8>::min_value();
  EXPECT_EQ(toPrettyString(val1), "00");

  UBigInteger<16> val2 = UBigInteger<16>::max_value();
  EXPECT_EQ(toPrettyString(val2), "ffff");
  val2 = UBigInteger<16>::zero_value();
  EXPECT_EQ(toPrettyString(val2), "0000");
  val2 = UBigInteger<16>::min_value();
  EXPECT_EQ(toPrettyString(val2), "0000");

  UBigInteger<32> val3 = UBigInteger<32>::max_value();
  EXPECT_EQ(toPrettyString(val3), "ffffffff");
  val3 = UBigInteger<32>::zero_value();
  EXPECT_EQ(toPrettyString(val3), "00000000");
  val3 = UBigInteger<32>::min_value();
  EXPECT_EQ(toPrettyString(val3), "00000000");
}
