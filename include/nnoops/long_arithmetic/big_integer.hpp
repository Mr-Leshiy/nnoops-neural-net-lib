#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_

#include <stdint.h>

#include <array>
#include <string>
#include <type_traits>

#include "nnoops/strutil.hpp"

namespace nnoops {

// Representation on the integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct BigInteger {
  BigInteger() = default;

  BigInteger(const BigInteger<SIZE>& val) : sign(val.sign), data(val.data) {}

  BigInteger(BigInteger<SIZE>&& val)
      : sign(std::move(val.sign)), data(std::move(val.data)) {}

  BigInteger<SIZE>& operator=(const BigInteger<SIZE>& val) {
    this->sign = val.sign;
    this->data = val.data;
    return *this;
  }

  BigInteger<SIZE>& operator=(BigInteger<SIZE>&& val) {
    this->sign = std::move(val.sign);
    this->data = std::move(val.data);
    return *this;
  }

  BigInteger(uint8_t val) : sign(true) {
    assert(data.size() >= 1 && "BigInteger has a small type");
    data[0] = (uint8_t)(val);
    for (size_t i = 1; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(uint16_t val) : sign(true) {
    assert(data.size() >= 2 && "BigInteger has a small type");
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    for (size_t i = 2; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(uint32_t val) : sign(true) {
    assert(data.size() >= 4 && "BigInteger has a small type");
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    data[2] = (uint8_t)(val >> 16);
    data[3] = (uint8_t)(val >> 24);
    for (size_t i = 4; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(uint64_t val) : sign(true) {
    assert(data.size() >= 8 && "BigInteger has a small type");
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    data[2] = (uint8_t)(val >> 16);
    data[3] = (uint8_t)(val >> 24);
    data[4] = (uint8_t)(val >> 32);
    data[5] = (uint8_t)(val >> 40);
    data[6] = (uint8_t)(val >> 48);
    data[7] = (uint8_t)(val >> 56);
    for (size_t i = 8; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(int8_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(data.size() >= 1 && "BigInteger has a small type");
    val = abs(val);
    data[0] = (uint8_t)(val);
    for (size_t i = 1; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(int16_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(data.size() >= 2 && "BigInteger has a small type");
    val = abs(val);
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    for (size_t i = 2; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(int32_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(data.size() >= 4 && "BigInteger has a small type");
    val = abs(val);
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    data[2] = (uint8_t)(val >> 16);
    data[3] = (uint8_t)(val >> 24);
    for (size_t i = 4; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  BigInteger(int64_t val) : sign(val >= 0 ? sign = true : sign = false) {
    assert(data.size() >= 8 && "BigInteger has a small type");
    val = abs(val);
    data[0] = (uint8_t)(val);
    data[1] = (uint8_t)(val >> 8);
    data[2] = (uint8_t)(val >> 16);
    data[3] = (uint8_t)(val >> 24);
    data[4] = (uint8_t)(val >> 32);
    data[5] = (uint8_t)(val >> 40);
    data[6] = (uint8_t)(val >> 48);
    data[7] = (uint8_t)(val >> 56);
    for (size_t i = 8; i < data.size(); ++i) {
      data[i] = 0;
    }
  }

  bool isPositive() const { return sign; }

  bool isNegative() const { return !sign; }

  BigInteger<SIZE> operator-() const {
    BigInteger<SIZE> ret = *this;
    ret.sign = this->sign == true ? false : true;
    return ret;
  }

  BigInteger<SIZE>& operator+=(const BigInteger<SIZE>& b) {
    int64_t carry = 0;
    bool res_sign = true;
    for (size_t i = 0; i < data.size(); ++i) {
      int64_t val1 = this->data[i] * (this->sign == false ? -1 : 1);
      int64_t val2 = b.data[i] * (b.sign == false ? -1 : 1);
      carry *= (res_sign == false ? -1 : 1);
      int64_t n = carry + val1 + val2;
      if (n < 0) {
        res_sign = false;
      }
      if (n > 0) {
        res_sign = true;
      }
      n = abs(n);
      this->data[i] = n & 0xff;
      carry = n >> 8;
    }
    this->sign = res_sign;
    return *this;
  }

  friend inline const BigInteger<SIZE> operator+(const BigInteger<SIZE>& a,
                                                 const BigInteger<SIZE>& b) {
    return BigInteger<SIZE>(a) += b;
  }

  bool operator==(const BigInteger<SIZE>& val) const {
    return this->sign == val.sign && this->data == val.data;
  }

  bool operator!=(const BigInteger<SIZE>& val) const { return !(*this == val); }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const BigInteger<SIZE>& b) const {
    if (this->sign == true && b.sign == false) {
      return 1;
    }
    if (this->sign == false && b.sign == true) {
      return -1;
    }

    for (int64_t i = (int64_t)(data.size() - 1); i != 0; --i) {
      if (this->data[i] < b.data[i]) {
        return this->sign == true ? -1 : 1;
      }
      if (this->data[i] > b.data[i]) {
        return this->sign == true ? -1 : 1;
      }
    }

    return 0;
  }

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

  friend std::string toPrettyString(const BigInteger<SIZE>& val) {
    if (val.sign) {
      return HexStr(val.data.rbegin(), val.data.rend());
    } else {
      return "-" + HexStr(val.data.rbegin(), val.data.rend());
    }
  }

 private:
  bool sign{false};
  std::array<uint8_t, SIZE / 8> data{};
};

}  // namespace nnoops

#endif
