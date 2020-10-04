#include <math.h>

#include "nnoops/long_arithmetic/big_decimal.hpp"

namespace nnoops {

std::string toPrettyString(const BigDecimal& val) {
  std::string result = val.sign == false ? "-" : "";
  return result + std::to_string(val.integer_part) + "." +
         std::to_string(val.decimal_part);
}

BigDecimal::BigDecimal(const double& val)
    : sign(val >= 0 ? true : false),
      integer_part(sign ? val : -1 * val),
      decimal_part(0) {}

}  // namespace nnoops