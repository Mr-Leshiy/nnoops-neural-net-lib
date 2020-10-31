#include "nnoops/long_arithmetic/signed_big_integer.hpp"

namespace nnoops {

template struct BigInteger<8>;
template struct BigInteger<16>;
template struct BigInteger<32>;
template struct BigInteger<64>;
template struct BigInteger<128>;
template struct BigInteger<256>;
template struct BigInteger<512>;
template struct BigInteger<1024>;

}  // namespace nnoops