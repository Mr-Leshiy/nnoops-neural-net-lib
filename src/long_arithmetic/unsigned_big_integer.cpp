#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

template struct UBigInteger<8, uint8_t>;
template struct UBigInteger<16, uint8_t>;
template struct UBigInteger<32, uint8_t>;
template struct UBigInteger<64, uint8_t>;
template struct UBigInteger<128, uint8_t>;
template struct UBigInteger<256, uint8_t>;
template struct UBigInteger<512, uint8_t>;
template struct UBigInteger<1024, uint8_t>;
template struct UBigInteger<2048, uint8_t>;
template struct UBigInteger<4096, uint8_t>;

template struct UBigInteger<16, uint16_t>;
template struct UBigInteger<32, uint16_t>;
template struct UBigInteger<64, uint16_t>;
template struct UBigInteger<128, uint16_t>;
template struct UBigInteger<256, uint16_t>;
template struct UBigInteger<512, uint16_t>;
template struct UBigInteger<1024, uint16_t>;
template struct UBigInteger<2048, uint16_t>;
template struct UBigInteger<4096, uint16_t>;

template struct UBigInteger<32, uint32_t>;
template struct UBigInteger<64, uint32_t>;
template struct UBigInteger<128, uint32_t>;
template struct UBigInteger<256, uint32_t>;
template struct UBigInteger<512, uint32_t>;
template struct UBigInteger<1024, uint32_t>;
template struct UBigInteger<2048, uint32_t>;
template struct UBigInteger<4096, uint32_t>;

}  // namespace nnoops
