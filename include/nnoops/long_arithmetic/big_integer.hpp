#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_

#include <stdint.h>

#include <array>
#include <type_traits>

namespace nnoops {

// Representation on the integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct BigInteger {
  BigInteger() = default;

  BigInteger(uint8_t val) : sign(true) {
    assert(value.size() >= 1 && "BigInteger has a small type");
    value[0] = (uint8_t)(val);
    for (size_t i = 1; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(uint16_t val) : sign(true) {
    assert(value.size() >= 2 && "BigInteger has a small type");
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    for (size_t i = 2; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(uint32_t val) : sign(true) {
    assert(value.size() >= 4 && "BigInteger has a small type");
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    value[2] = (uint8_t)(val >> 16);
    value[3] = (uint8_t)(val >> 24);
    for (size_t i = 4; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(uint64_t val) : sign(true) {
    assert(value.size() >= 8 && "BigInteger has a small type");
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    value[2] = (uint8_t)(val >> 16);
    value[3] = (uint8_t)(val >> 24);
    value[4] = (uint8_t)(val >> 32);
    value[5] = (uint8_t)(val >> 40);
    value[6] = (uint8_t)(val >> 48);
    value[7] = (uint8_t)(val >> 56);
    for (size_t i = 8; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(int8_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(value.size() >= 1 && "BigInteger has a small type");
    val = abs(val);
    value[0] = (uint8_t)(val);
    for (size_t i = 1; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(int16_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(value.size() >= 2 && "BigInteger has a small type");
    val = abs(val);
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    for (size_t i = 2; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(int32_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(value.size() >= 4 && "BigInteger has a small type");
    val = abs(val);
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    value[2] = (uint8_t)(val >> 16);
    value[3] = (uint8_t)(val >> 24);
    for (size_t i = 4; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  BigInteger(int64_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(value.size() >= 8 && "BigInteger has a small type");
    val = abs(val);
    value[0] = (uint8_t)(val);
    value[1] = (uint8_t)(val >> 8);
    value[2] = (uint8_t)(val >> 16);
    value[3] = (uint8_t)(val >> 24);
    value[4] = (uint8_t)(val >> 32);
    value[5] = (uint8_t)(val >> 40);
    value[6] = (uint8_t)(val >> 48);
    value[7] = (uint8_t)(val >> 56);
    for (size_t i = 8; i < value.size(); ++i) {
      value[i] = 0;
    }
  }

  bool isPositive() const { return sign; }

  bool isNegative() const { return !sign; }

 private:
  bool sign{false};
  std::array<uint8_t, SIZE / 8> value{};
};

}  // namespace nnoops

#endif