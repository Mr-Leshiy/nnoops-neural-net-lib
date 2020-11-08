#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

using namespace nnoops;

void division_check1(uint64_t a, uint64_t b) {
  printf("[          ][ INFO ] value a: %lu, value b: %lu \n", a, b);
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a / b;
  EXPECT_EQ(val1 / val2, UBigInteger<64>(c));
  c = b / a;
  EXPECT_EQ(val2 / val1, UBigInteger<64>(c));
  EXPECT_EQ(val1 / val1, UBigInteger<64>(1));
  EXPECT_EQ(val2 / val2, UBigInteger<64>(1));
}

void division_check2(uint64_t a, uint64_t b) {
  printf("[          ][ INFO ] value a: %lu, value b: %lu \n", a, b);
  UBigInteger<64> val1 = a;
  UBigInteger<64> val2 = b;
  uint64_t c = a % b;
  EXPECT_EQ(val1 % val2, UBigInteger<64>(c));
  c = b % a;
  EXPECT_EQ(val2 % val1, UBigInteger<64>(c));
  EXPECT_EQ(val1 % val1, UBigInteger<64>(0));
  EXPECT_EQ(val2 % val2, UBigInteger<64>(0));
}

// TEST(UBigInteger, heavy_division_test) {
//   for (uint64_t a = 1; a < 1000; ++a) {
//     for (uint64_t b = 1; b < 1000; ++b) {
//       division_check1(a, b);
//     }
//   }

//   for (uint64_t a = (std::numeric_limits<uint64_t>::max() - 1000);
//        a < std::numeric_limits<uint64_t>::max();
//        ++a) {
//     for (uint64_t b = (std::numeric_limits<uint64_t>::max() - 1000);
//          b < std::numeric_limits<uint64_t>::max();
//          ++b) {
//       division_check1(a, b);
//     }
//   }

//   for (uint64_t a = (std::numeric_limits<uint64_t>::max() - 1000);
//        a < std::numeric_limits<uint64_t>::max();
//        ++a) {
//     for (uint64_t b = 1; b < 1000; ++b) {
//       division_check1(a, b);
//     }
//   }
// }

TEST(UBigInteger, heavy_division_test2) {
  for (uint64_t a = 1; a < 1000; ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      division_check2(a, b);
    }
  }

  for (uint64_t a = (std::numeric_limits<uint64_t>::max() - 1000);
       a < std::numeric_limits<uint64_t>::max();
       ++a) {
    for (uint64_t b = (std::numeric_limits<uint64_t>::max() - 1000);
         b < std::numeric_limits<uint64_t>::max();
         ++b) {
      division_check2(a, b);
    }
  }

  for (uint64_t a = (std::numeric_limits<uint64_t>::max() - 1000);
       a < std::numeric_limits<uint64_t>::max();
       ++a) {
    for (uint64_t b = 1; b < 1000; ++b) {
      division_check2(a, b);
    }
  }
}