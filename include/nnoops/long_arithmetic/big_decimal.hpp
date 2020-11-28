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
template <uint64_t SIZE = 64, typename BASE_T = uint32_t>
struct BigDecimal {
  using BigDecimalT = BigDecimal<SIZE, BASE_T>;
  using BigIntegerT = BigInteger<SIZE, BASE_T>;

  ~BigDecimal() = default;

  BigDecimal() = default;

  BigDecimal(const BigDecimalT& val)
      : exponent(val.exponent), mantissa(val.mantissa) {}

  BigDecimal(BigDecimalT&& val)
      : exponent(std::move(val.exponent)), mantissa(std::move(val.mantissa)) {}

  BigDecimalT& operator=(const BigDecimalT& val) {
    this->exponent = val.exponent;
    this->mantissa = val.mantissa;
    return *this;
  }

  BigDecimalT& operator=(BigDecimalT&& val) {
    this->exponent = std::move(val.exponent);
    this->mantissa = std::move(val.mantissa);
    return *this;
  }

  BigDecimal(double val) { (void)val; }

  friend std::string toPrettyString(const BigDecimalT& val) {
    return toPrettyString(val.mantissa) + "e" + std::to_string(val.exponent);
  }

 private:
  int64_t exponent{};
  BigIntegerT mantissa{};
};

}  // namespace nnoops

#endif
