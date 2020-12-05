#include <gtest/gtest.h>

#include <limits>

#include "nnoops/long_arithmetic/big_decimal.hpp"

using namespace nnoops;

TEST(BigDecimal, multiplication_test) {
  /*
   using BigDecimalT = BigDecimal<>;
   BigDecimalT val1 = 3124.3312;
   BigDecimalT val2 = -12.41551;

   val1 *= val2;

   EXPECT_EQ(val1, BigDecimalT(-38790.165256912));

   val1 = 3124.3312;

   EXPECT_EQ(val1 * val2, BigDecimalT(-38790.165256912));
   EXPECT_EQ(val2 * val1, BigDecimalT(-38790.165256912));

   val2 *= -1;

   EXPECT_EQ(val1 * val2, BigDecimalT(38790.165256912));
   EXPECT_EQ(val2 * val1, BigDecimalT(38790.165256912));
   */
}

TEST(BigDecimal, toPrettyString_test) {
  BigDecimal<> val(1234);

  EXPECT_EQ(toPrettyString(val), "0.4d2*e^(4)");

  val = 1234000000;

  EXPECT_EQ(toPrettyString(val), "0.4d2*e^(a)");

  val = -1234;

  EXPECT_EQ(toPrettyString(val), "0.-4d2*e^(4)");

  val = -1234000000;

  EXPECT_EQ(toPrettyString(val), "0.-4d2*e^(a)");

  val = 124.2134;

  EXPECT_EQ(toPrettyString(val), "0.12f416*e^(3)");

  val = -124.2134;

  EXPECT_EQ(toPrettyString(val), "0.-12f416*e^(3)");

  val = 0.00124;

  EXPECT_EQ(toPrettyString(val), "0.7c*e^(-2)");

  val = -0.00124;

  EXPECT_EQ(toPrettyString(val), "0.-7c*e^(-2)");
}
