#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

template struct UBigInteger<32>;
template struct UBigInteger<64>;
template struct UBigInteger<128>;
template struct UBigInteger<256>;
template struct UBigInteger<512>;
template struct UBigInteger<1024>;
template struct UBigInteger<2048>;
template struct UBigInteger<4096>;

}  // namespace nnoops
