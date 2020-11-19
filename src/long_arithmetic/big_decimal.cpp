#include <math.h>

#include <cassert>

#include "nnoops/long_arithmetic/big_decimal.hpp"

namespace nnoops {

template struct BigDecimal<8>;
template struct BigDecimal<16>;
template struct BigDecimal<32>;
template struct BigDecimal<64>;
template struct BigDecimal<128>;
template struct BigDecimal<256>;
template struct BigDecimal<512>;
template struct BigDecimal<1024>;
template struct BigDecimal<2048>;
template struct BigDecimal<4096>;

}  // namespace nnoops
