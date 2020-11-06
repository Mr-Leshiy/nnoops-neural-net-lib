#include <gtest/gtest.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

TEST(UBigInteger, heavy_division_test) {
  UBigInteger<64> val1;
  UBigInteger<64> val2;

  uint64_t c;
  for (uint64_t a = 1; a < 1000; ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      val1 = a;
      val2 = b;
      c = a / b;
      EXPECT_EQ(val1 / val2, UBigInteger<64>(c));
      c = b / a;
      EXPECT_EQ(val2 / val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 / val1, UBigInteger<64>(1));
      EXPECT_EQ(val2 / val2, UBigInteger<64>(1));
    }
  }

  for (uint64_t a = 1000; a < 1000000; ++a) {
    for (uint64_t b = 1000; b < 1000000; ++b) {
      val1 = a;
      val2 = b;
      c = a / b;
      EXPECT_EQ(val1 / val2, UBigInteger<64>(c));
      c = b / a;
      EXPECT_EQ(val2 / val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 / val1, UBigInteger<64>(1));
      EXPECT_EQ(val2 / val2, UBigInteger<64>(1));
    }
  }

  for (uint64_t a = 1000; a < 1000000; ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      val1 = a;
      val2 = b;
      c = a / b;
      EXPECT_EQ(val1 / val2, UBigInteger<64>(c));
      c = b / a;
      EXPECT_EQ(val2 / val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 / val1, UBigInteger<64>(1));
      EXPECT_EQ(val2 / val2, UBigInteger<64>(1));
    }
  }
}

TEST(UBigInteger, heavy_division_test2) {
  UBigInteger<64> val1;
  UBigInteger<64> val2;

  uint64_t c;
  for (uint64_t a = 1; a < 1000; ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      val1 = a;
      val2 = b;
      c = a % b;
      EXPECT_EQ(val1 % val2, UBigInteger<64>(c));
      c = b % a;
      EXPECT_EQ(val2 % val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 % val1, UBigInteger<64>(0));
      EXPECT_EQ(val2 % val2, UBigInteger<64>(0));
    }
  }

  for (uint64_t a = 1000; a < 1000000; ++a) {
    for (uint64_t b = 1000; b < 1000000; ++b) {
      val1 = a;
      val2 = b;
      c = a % b;
      EXPECT_EQ(val1 % val2, UBigInteger<64>(c));
      c = b % a;
      EXPECT_EQ(val2 % val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 % val1, UBigInteger<64>(0));
      EXPECT_EQ(val2 % val2, UBigInteger<64>(0));
    }
  }

    for (uint64_t a = 1000; a < 1000000; ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      val1 = a;
      val2 = b;
      c = a % b;
      EXPECT_EQ(val1 % val2, UBigInteger<64>(c));
      c = b % a;
      EXPECT_EQ(val2 % val1, UBigInteger<64>(c));
      EXPECT_EQ(val1 % val1, UBigInteger<64>(0));
      EXPECT_EQ(val2 % val2, UBigInteger<64>(0));
    }
  }
}