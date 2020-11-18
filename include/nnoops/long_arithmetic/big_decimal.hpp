#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_

#include <math.h>
#include <stdint.h>

#include <string>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

namespace nnoops {

// Representation on the big decimal with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
// actual size of the BigDecimal equals to SIZE / 2
// representation is equal to quotient of a / b
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct BigDecimal {
  BigDecimal() = default;

  BigDecimal(const BigDecimal& val) : a(val.a), b(val.b) {}

  BigDecimal(BigDecimal&& val) : a(std::move(val.a)), b(std::move(val.b)) {}

  BigDecimal& operator=(const BigDecimal<SIZE>& val) {
    this->a = val.a;
    this->b = val.b;
    return *this;
  }

  BigDecimal& operator=(BigDecimal<SIZE>&& val) {
    this->a = std::move(val.a);
    this->b = std::move(val.b);
    return *this;
  }

  BigDecimal(uint64_t a, uint64_t b) : a(a), b(b) {}

  friend std::string toPrettyString(const BigDecimal<SIZE>& val) {
    return toPrettyString(val.a) + "/" + toPrettyString(val.b);
  }

 private:
  BigInteger<SIZE> a;
  UBigInteger<SIZE> b;
};

extern template struct BigDecimal<8>;
extern template struct BigDecimal<16>;
extern template struct BigDecimal<32>;
extern template struct BigDecimal<64>;
extern template struct BigDecimal<128>;
extern template struct BigDecimal<256>;
extern template struct BigDecimal<512>;
extern template struct BigDecimal<1024>;
extern template struct BigDecimal<2048>;
extern template struct BigDecimal<4096>;

}  // namespace nnoops

#endif
