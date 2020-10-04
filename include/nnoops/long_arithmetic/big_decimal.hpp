#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_

#include <math.h>
#include <stdint.h>

#include <string>

namespace nnoops {

struct BigDecimal {
  BigDecimal() = default;

  BigDecimal(const BigDecimal& val)
      : sign(val.sign),
        integer_part(val.integer_part),
        decimal_part(val.decimal_part) {}

  BigDecimal(BigDecimal&& val)
      : sign(std::move(val.sign)),
        integer_part(std::move(val.integer_part)),
        decimal_part(std::move(val.decimal_part)) {}

  BigDecimal& operator=(const BigDecimal& val) {
    this->sign = val.sign;
    this->integer_part = val.integer_part;
    this->decimal_part = val.decimal_part;
    return *this;
  }

  BigDecimal& operator=(BigDecimal&& val) {
    this->sign = std::move(val.sign);
    this->integer_part = std::move(val.integer_part);
    this->decimal_part = std::move(val.decimal_part);
    return *this;
  }

  BigDecimal(const std::string& val);

  BigDecimal(const double& val);

  friend std::string toPrettyString(const BigDecimal& val);

 private:
  void optimizeDecimalPart();

  bool sign{true};
  uint64_t integer_part{0};
  uint64_t decimal_part{0};
};

}  // namespace nnoops

#endif