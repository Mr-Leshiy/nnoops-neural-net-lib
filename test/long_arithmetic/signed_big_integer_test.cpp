#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

TEST(BigInteger, comparison_test) {}

TEST(BigInteger, addition_substraction_test) {}

TEST(BigInteger, multiplication_test) {}

TEST(BigInteger, division_test) {}

TEST(BigInteger, division_test2) {}

TEST(BigInteger, toPrettyString_test) {
    BigInteger val(1234);

    EXPECT_EQ(toPrettyString(val), "4d2");

    val = -1235;

    EXPECT_EQ(toPrettyString(val), "-4d3");
}