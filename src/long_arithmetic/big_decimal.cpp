#include <math.h>

#include <cassert>

#include "nnoops/long_arithmetic/big_decimal.hpp"

namespace nnoops {

std::string toPrettyString(const BigDecimal& val) {
  std::string result = val.sign == false ? "-" : "";
  return result + std::to_string(val.integer_part) + "." +
         std::to_string(val.decimal_part);
}

BigDecimal::BigDecimal(const std::string& val) {
  assert(val != "" &&
         "string should have the following representation 12.12 or -13.41");

  bool int_part = true;
  for (auto ch = val.begin(); ch != val.end(); ++ch) {
    if (*ch == '-' && ch == val.begin()) {
      this->sign = false;
      continue;
    }

    assert(isdigit(*ch) || *ch == '.' && "string has invalid character");

    if (*ch == '.') {
      int_part = false;
      continue;
    }

    if (int_part) {
      integer_part *= 10;
      integer_part += *ch - '0';
    } else {
      decimal_part *= 10;
      decimal_part += *ch - '0';
    }
  }
}

BigDecimal::BigDecimal(const double& val)
    : BigDecimal::BigDecimal(std::to_string(val)) {}

}  // namespace nnoops