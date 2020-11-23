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
          typename = typename std::enable_if<SIZE % 32 == 0 && SIZE != 0>::type>
struct BigDecimal {
  ~BigDecimal() = default;

  BigDecimal() = default;

  BigDecimal(const BigDecimal& val)
      : exponent(val.exponent), mantissa(val.mantissa) {}

  BigDecimal(BigDecimal&& val)
      : exponent(std::move(val.exponent)), mantissa(std::move(val.mantissa)) {}

  BigDecimal& operator=(const BigDecimal<SIZE>& val) {
    this->exponent = val.exponent;
    this->mantissa = val.mantissa;
    return *this;
  }

  BigDecimal& operator=(BigDecimal<SIZE>&& val) {
    this->exponent = std::move(val.exponent);
    this->mantissa = std::move(val.mantissa);
    return *this;
  }

  BigDecimal(double val) { (void)val; }

  friend std::string toPrettyString(const BigDecimal<SIZE>& val) {
    return toPrettyString(val.mantissa) + "e" + std::to_string(val.exponent);
  }

 private:
  int64_t exponent{};
  BigInteger<SIZE> mantissa{};
};

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
