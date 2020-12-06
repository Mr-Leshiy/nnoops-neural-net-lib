#include <math.h>

#include <cassert>

#include "nnoops/long_arithmetic/big_float.hpp"

namespace nnoops {

template struct BigFloat<32>;
template struct BigFloat<64>;
template struct BigFloat<128>;
template struct BigFloat<256>;
template struct BigFloat<512>;
template struct BigFloat<1024>;
template struct BigFloat<2048>;
template struct BigFloat<4096>;

}  // namespace nnoops
