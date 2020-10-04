#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_

#include <math.h>
#include <stdint.h>

#include <string>

namespace nnoops {

struct BigDecimal {
  BigDecimal() = default;

  BigDecimal(const std::string& val);

  BigDecimal(const double& val);

  friend std::string toPrettyString(const BigDecimal& val);

 private:
  bool sign{true};
  uint64_t integer_part{0};
  uint64_t decimal_part{0};
};

}  // namespace nnoops

#endif