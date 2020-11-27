#include "nnoops/long_arithmetic/signed_big_integer.hpp"

namespace nnoops {

template struct BigInteger<8, uint8_t>;
template struct BigInteger<16, uint8_t>;
template struct BigInteger<32, uint8_t>;
template struct BigInteger<64, uint8_t>;
template struct BigInteger<128, uint8_t>;
template struct BigInteger<256, uint8_t>;
template struct BigInteger<512, uint8_t>;
template struct BigInteger<1024, uint8_t>;
template struct BigInteger<2048, uint8_t>;
template struct BigInteger<4096, uint8_t>;

template struct BigInteger<16, uint16_t>;
template struct BigInteger<32, uint16_t>;
template struct BigInteger<64, uint16_t>;
template struct BigInteger<128, uint16_t>;
template struct BigInteger<256, uint16_t>;
template struct BigInteger<512, uint16_t>;
template struct BigInteger<1024, uint16_t>;
template struct BigInteger<2048, uint16_t>;
template struct BigInteger<4096, uint16_t>;

template struct BigInteger<32, uint32_t>;
template struct BigInteger<64, uint32_t>;
template struct BigInteger<128, uint32_t>;
template struct BigInteger<256, uint32_t>;
template struct BigInteger<512, uint32_t>;
template struct BigInteger<1024, uint32_t>;
template struct BigInteger<2048, uint32_t>;
template struct BigInteger<4096, uint32_t>;

}  // namespace nnoops
