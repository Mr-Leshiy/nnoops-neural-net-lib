#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

template struct UBigInteger<8>;
template struct UBigInteger<16>;
template struct UBigInteger<32>;
template struct UBigInteger<64>;

}  // namespace nnoops