#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

template <uint64_t SIZE, typename BASE_T>
struct UBigIntegerTestCase {
  const static uint64_t size = SIZE;
  using base_t = BASE_T;
};

template <typename T>
struct UBigIntegerTest : public ::testing::Test {};

TYPED_TEST_SUITE_P(UBigIntegerTest);

TYPED_TEST_P(UBigIntegerTest, comparison_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  UBigIntegerT val1(431);
  UBigIntegerT val2(25423);

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
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  UBigIntegerT val1(66576);
  UBigIntegerT val2(53648);

  val1 += val2;

  EXPECT_EQ(val1, UBigIntegerT(120224));

  val1 -= val2;

  EXPECT_EQ(val1, UBigIntegerT(66576));

  EXPECT_EQ(val1 + val2, UBigIntegerT(120224));
  EXPECT_EQ(val2 + val1, UBigIntegerT(120224));

  EXPECT_EQ(val1 - val2, UBigIntegerT(12928));

  EXPECT_EQ(val1++, UBigIntegerT(66576));
  EXPECT_EQ(val1, UBigIntegerT(66577));

  EXPECT_EQ(++val1, UBigIntegerT(66578));
  EXPECT_EQ(val1, UBigIntegerT(66578));

  EXPECT_EQ(val1--, UBigIntegerT(66578));
  EXPECT_EQ(val1, UBigIntegerT(66577));

  EXPECT_EQ(--val1, UBigIntegerT(66576));
  EXPECT_EQ(val1, UBigIntegerT(66576));

  UBigIntegerT val5(255);

  EXPECT_EQ(++val5, UBigIntegerT(256));
  EXPECT_EQ(--val5, UBigIntegerT(255));
}

TYPED_TEST_P(UBigIntegerTest, multiplication_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  UBigIntegerT val1(1234);
  UBigIntegerT val2(4321);

  val1 *= val2;

  EXPECT_EQ(val1, UBigIntegerT(5332114));

  val1 = 1234;

  EXPECT_EQ(val1 * val2, UBigIntegerT(5332114));
  EXPECT_EQ(val2 * val1, UBigIntegerT(5332114));

  UBigIntegerT val3 = 125;
  UBigIntegerT val4 = 2;

  EXPECT_EQ(val3 * val4, UBigIntegerT(250));
  EXPECT_EQ(val4 * val3, UBigIntegerT(250));
}

TYPED_TEST_P(UBigIntegerTest, division_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  UBigIntegerT val1(41351);
  UBigIntegerT val2(5423);

  EXPECT_EQ(val1 / val2, UBigIntegerT(7));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigIntegerT(178));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigIntegerT(6726));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 / val2, UBigIntegerT(6206255));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 / val2, UBigIntegerT(3007261));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 / val2, UBigIntegerT(23774));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 / val2, UBigIntegerT(1));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));

  val1 = 41346146161;
  val2 = 10;

  EXPECT_EQ(val1 / val2, UBigIntegerT(4134614616));
  EXPECT_EQ(val2 / val1, UBigIntegerT(0));
  EXPECT_EQ(val1 / val1, UBigIntegerT(1));
  EXPECT_EQ(val2 / val2, UBigIntegerT(1));
}

TYPED_TEST_P(UBigIntegerTest, division_test2) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  UBigIntegerT val1(41351);
  UBigIntegerT val2(5423);

  EXPECT_EQ(val1 % val2, UBigIntegerT(3390));
  EXPECT_EQ(val2 % val1, UBigIntegerT(5423));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 357;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigIntegerT(1));
  EXPECT_EQ(val2 % val1, UBigIntegerT(2));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 13452;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigIntegerT(0));
  EXPECT_EQ(val2 % val1, UBigIntegerT(2));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 12412511;
  val2 = 2;

  EXPECT_EQ(val1 % val2, UBigIntegerT(1));
  EXPECT_EQ(val2 % val1, UBigIntegerT(2));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 1235984556;
  val2 = 411;

  EXPECT_EQ(val1 % val2, UBigIntegerT(285));
  EXPECT_EQ(val2 % val1, UBigIntegerT(411));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 325685126;
  val2 = 13699;

  EXPECT_EQ(val1 % val2, UBigIntegerT(5100));
  EXPECT_EQ(val2 % val1, UBigIntegerT(13699));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 999991;
  val2 = 999990;

  EXPECT_EQ(val1 % val2, UBigIntegerT(1));
  EXPECT_EQ(val2 % val1, UBigIntegerT(999990));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));

  val1 = 41346146161;
  val2 = 10;

  EXPECT_EQ(val1 % val2, UBigIntegerT(1));
  EXPECT_EQ(val2 % val1, UBigIntegerT(10));
  EXPECT_EQ(val1 % val1, UBigIntegerT(0));
  EXPECT_EQ(val2 % val2, UBigIntegerT(0));
}

TYPED_TEST_P(UBigIntegerTest, exception_handling_test) {
  const static uint64_t size = TypeParam::size;
  using base_t = typename TypeParam::base_t;
  using UBigIntegerT = UBigInteger<size, base_t>;

  EXPECT_THROW(UBigIntegerT tmp(-12), arith_error);

  EXPECT_THROW(UBigIntegerT::max_value() + 1, arith_error);
  EXPECT_THROW(1 + UBigIntegerT::max_value(), arith_error);
  EXPECT_THROW(++UBigIntegerT::max_value(), arith_error);
  EXPECT_THROW(UBigIntegerT::max_value()++, arith_error);
  EXPECT_THROW(2 * UBigIntegerT::max_value(), arith_error);
  EXPECT_THROW(UBigIntegerT::max_value() * 2, arith_error);

  EXPECT_THROW(UBigIntegerT::min_value() - 1, arith_error);
  EXPECT_THROW(--UBigIntegerT::min_value(), arith_error);
  EXPECT_THROW(UBigIntegerT::min_value()--, arith_error);
}

REGISTER_TYPED_TEST_SUITE_P(UBigIntegerTest,
                            comparison_test,
                            addition_substraction_test,
                            multiplication_test,
                            division_test,
                            division_test2,
                            exception_handling_test);

typedef ::testing::Types<UBigIntegerTestCase<64, uint8_t>,
                         UBigIntegerTestCase<128, uint8_t>,
                         UBigIntegerTestCase<256, uint8_t>,
                         UBigIntegerTestCase<512, uint8_t>,
                         UBigIntegerTestCase<1024, uint8_t>,
                         UBigIntegerTestCase<2048, uint8_t>,
                         UBigIntegerTestCase<4096, uint8_t>,
                         UBigIntegerTestCase<64, uint16_t>,
                         UBigIntegerTestCase<128, uint16_t>,
                         UBigIntegerTestCase<256, uint16_t>,
                         UBigIntegerTestCase<512, uint16_t>,
                         UBigIntegerTestCase<1024, uint16_t>,
                         UBigIntegerTestCase<2048, uint16_t>,
                         UBigIntegerTestCase<4096, uint16_t>,
                         UBigIntegerTestCase<64, uint32_t>,
                         UBigIntegerTestCase<128, uint32_t>,
                         UBigIntegerTestCase<256, uint32_t>,
                         UBigIntegerTestCase<512, uint32_t>,
                         UBigIntegerTestCase<1024, uint32_t>,
                         UBigIntegerTestCase<2048, uint32_t>,
                         UBigIntegerTestCase<4096, uint32_t>>
    UBigIntegerTestCases;

INSTANTIATE_TYPED_TEST_SUITE_P(UBigIntegerTestSuite,
                               UBigIntegerTest,
                               UBigIntegerTestCases);

TEST(UBigInteger, small_comparison_test) {
  using UBigIntegerT = UBigInteger<8, uint8_t>;

  UBigIntegerT val1((uint8_t)11);
  UBigIntegerT val2((uint8_t)123);

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

TEST(UBigInteger, small_addition_substraction_test) {
  using UBigIntegerT = UBigInteger<8, uint8_t>;

  UBigIntegerT val1((uint8_t)123);
  UBigIntegerT val2((uint8_t)84);

  EXPECT_EQ(val1 + val2, UBigIntegerT((uint8_t)207));
  EXPECT_EQ(val2 + val1, UBigIntegerT((uint8_t)207));

  EXPECT_EQ(val1 - val2, UBigIntegerT((uint8_t)39));

  EXPECT_EQ(val1++, UBigIntegerT((uint8_t)123));
  EXPECT_EQ(val1, UBigIntegerT((uint8_t)124));

  EXPECT_EQ(++val1, UBigIntegerT((uint8_t)125));
  EXPECT_EQ(val1, UBigIntegerT((uint8_t)125));

  EXPECT_EQ(val1--, UBigIntegerT((uint8_t)125));
  EXPECT_EQ(val1, UBigIntegerT((uint8_t)124));

  EXPECT_EQ(--val1, UBigIntegerT((uint8_t)123));
  EXPECT_EQ(val1, UBigIntegerT((uint8_t)123));
}

TEST(UBigInteger, small_multiplication_test) {
  using UBigIntegerT = UBigInteger<8, uint8_t>;

  UBigIntegerT val1((uint8_t)2);
  UBigIntegerT val2((uint8_t)124);

  EXPECT_EQ(val1 * val2, UBigIntegerT((uint8_t)248));
  EXPECT_EQ(val2 * val1, UBigIntegerT((uint8_t)248));
}

TEST(UBigInteger, small_division_test) {
  using UBigIntegerT = UBigInteger<8, uint8_t>;

  UBigIntegerT val1((uint8_t)123);
  UBigIntegerT val2((uint8_t)15);

  EXPECT_EQ(val1 / val2, UBigIntegerT((uint8_t)8));
  EXPECT_EQ(val2 / val1, UBigIntegerT((uint8_t)0));
  EXPECT_EQ(val1 / val1, UBigIntegerT((uint8_t)1));
  EXPECT_EQ(val2 / val2, UBigIntegerT((uint8_t)1));
}

TEST(UBigInteger, small_division_test2) {
  using UBigIntegerT = UBigInteger<8, uint8_t>;

  UBigIntegerT val1((uint8_t)123);
  UBigIntegerT val2((uint8_t)15);

  EXPECT_EQ(val1 % val2, UBigIntegerT((uint8_t)3));
  EXPECT_EQ(val2 % val1, UBigIntegerT((uint8_t)15));
  EXPECT_EQ(val1 % val1, UBigIntegerT((uint8_t)0));
  EXPECT_EQ(val2 % val2, UBigIntegerT((uint8_t)0));
}

TEST(UBigInteger, toPrettyString_test) {
  UBigInteger<> val(1234);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d2");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1234");

  val = 1235;

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d3");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1235");

  val = UBigInteger<>("4d2", NumFormat::HEX);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d2");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1234");

  val = UBigInteger<>("1235", NumFormat::DEC);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "4d3");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "1235");

  val = UBigInteger<>("00000213", NumFormat::DEC);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "d5");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "213");

  val = UBigInteger<>(
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000213",
      NumFormat::HEX);

  EXPECT_EQ(toPrettyString(val, NumFormat::HEX), "213");
  EXPECT_EQ(toPrettyString(val, NumFormat::DEC), "531");
}

TEST(UBigInteger, basic_values_test) {
  EXPECT_EQ(toPrettyString(UBigInteger<32>::max_value(), NumFormat::HEX),
            "ffffffff");
  EXPECT_EQ(toPrettyString(UBigInteger<32>::zero_value(), NumFormat::HEX), "0");
  EXPECT_EQ(toPrettyString(UBigInteger<32>::min_value(), NumFormat::HEX), "0");

  EXPECT_EQ(toPrettyString(UBigInteger<64>::max_value(), NumFormat::HEX),
            "ffffffffffffffff");
  EXPECT_EQ(toPrettyString(UBigInteger<64>::zero_value(), NumFormat::HEX), "0");
  EXPECT_EQ(toPrettyString(UBigInteger<64>::min_value(), NumFormat::HEX), "0");

  EXPECT_EQ(toPrettyString(UBigInteger<32>::max_value(), NumFormat::DEC),
            "4294967295");
  EXPECT_EQ(toPrettyString(UBigInteger<32>::zero_value(), NumFormat::DEC), "0");
  EXPECT_EQ(toPrettyString(UBigInteger<32>::min_value(), NumFormat::DEC), "0");

  EXPECT_EQ(toPrettyString(UBigInteger<64>::max_value(), NumFormat::DEC),
            "18446744073709551615");
  EXPECT_EQ(toPrettyString(UBigInteger<64>::zero_value(), NumFormat::DEC), "0");
  EXPECT_EQ(toPrettyString(UBigInteger<64>::min_value(), NumFormat::DEC), "0");
}
