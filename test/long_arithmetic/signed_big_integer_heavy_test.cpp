#include <gtest/gtest.h>
#include <limits.h>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

using namespace nnoops;

void comparison_check(int64_t a, int64_t b) {
    BigInteger<64> val1 = a;
    BigInteger<64> val2 = b;

}