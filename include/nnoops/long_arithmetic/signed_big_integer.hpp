#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_

#include <stdlib.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

// Representation on the signed integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct BigInteger : public UBigInteger<SIZE> {
  ~BigInteger() override = default;

  BigInteger() : UBigInteger<SIZE>() {}

  BigInteger(const BigInteger<SIZE>& val)
      : UBigInteger<SIZE>(val), sign(val.sign) {}

  BigInteger(BigInteger<SIZE>&& val)
      : UBigInteger<SIZE>(val), sign(std::move(val.sign)) {}

  BigInteger<SIZE>& operator=(const BigInteger<SIZE>& val) {
    UBigInteger<SIZE>::operator=(val);
    this->sign = val.sign;
    return *this;
  }

  BigInteger<SIZE>& operator=(BigInteger<SIZE>&& val) {
    UBigInteger<SIZE>::operator=(val);
    this->sign = std::move(val.sign);
    return *this;
  }

  BigInteger(uint8_t val) : UBigInteger<SIZE>(val), sign(true) {}

  BigInteger(uint16_t val) : UBigInteger<SIZE>(val), sign(true) {}

  BigInteger(uint32_t val) : UBigInteger<SIZE>(val), sign(true) {}

  BigInteger(uint64_t val) : UBigInteger<SIZE>(val), sign(true) {}

  BigInteger(int8_t val)
      : UBigInteger<SIZE>(abs(val)), sign(val >= 0 ? true : false) {}

  BigInteger(int16_t val)
      : UBigInteger<SIZE>(abs(val)), sign(val >= 0 ? true : false) {}

  BigInteger(int32_t val)
      : UBigInteger<SIZE>(abs(val)), sign(val >= 0 ? true : false) {}

  BigInteger(int64_t val)
      : UBigInteger<SIZE>(abs(val)), sign(val >= 0 ? true : false) {}

  bool operator==(const BigInteger<SIZE>& val) const {
    return this->sign == val.sign && UBigInteger<SIZE>::operator==(val);
  }

  bool operator!=(const BigInteger<SIZE>& val) const { return !(*this == val); }

  friend bool operator>(const BigInteger<SIZE>& a, const BigInteger<SIZE>& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const BigInteger<SIZE>& a, const BigInteger<SIZE>& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const BigInteger<SIZE>& a, const BigInteger<SIZE>& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const BigInteger<SIZE>& a, const BigInteger<SIZE>& b) {
    return a.compareTo(b) <= 0;
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const BigInteger<SIZE>& b) const {
    if (this->sign == false && b.sign == true) {
      return -1;
    }
    if (this->sign == true && b.sign == false) {
      return 1;
    }

    return b.sign == false ? -1 * UBigInteger<SIZE>::compareTo(b)
                           : UBigInteger<SIZE>::compareTo(b);
  }

  friend std::string toPrettyString(const BigInteger<SIZE>& val) {
    if (val.sign == true) {
      return toPrettyString(UBigInteger<SIZE>(val));
    } else {
      return "-" + toPrettyString(UBigInteger<SIZE>(val));
    }
  }

 private:
  // sign == true means positive number
  // sign == false means negative number
  bool sign = false;
};

extern template struct BigInteger<8>;
extern template struct BigInteger<16>;
extern template struct BigInteger<32>;
extern template struct BigInteger<64>;
extern template struct BigInteger<128>;
extern template struct BigInteger<256>;
extern template struct BigInteger<512>;
extern template struct BigInteger<1024>;

}  // namespace nnoops

#endif