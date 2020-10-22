#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_INTEGER_HPP_

#include <stdint.h>

#include <array>
#include <string>
#include <type_traits>

#include "nnoops/strutil.hpp"

namespace nnoops {

// Representation on the unsigned integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct UBigInteger {
  UBigInteger() = default;

  UBigInteger(const UBigInteger<SIZE>& val) : data(val.data) {}

  UBigInteger(UBigInteger<SIZE>&& val) : data(std::move(val.data)) {}

  UBigInteger<SIZE>& operator=(const UBigInteger<SIZE>& val) {
    this->data = val.data;
    return *this;
  }

  UBigInteger<SIZE>& operator=(UBigInteger<SIZE>&& val) {
    this->data = std::move(val.data);
    return *this;
  }

  UBigInteger(uint8_t val) { init(val); }

  UBigInteger(uint16_t val) { init(val); }

  UBigInteger(uint32_t val) { init(val); }

  UBigInteger(uint64_t val) { init(val); }

  UBigInteger(int8_t val) {
    assert(val >= 0 && "value should be positive");
    init((uint8_t)val);
  }

  UBigInteger(int16_t val) {
    assert(val >= 0 && "value should be positive");
    init((uint16_t)val);
  }

  UBigInteger(int32_t val) {
    assert(val >= 0 && "value should be positive");
    init((uint32_t)val);
  }

  UBigInteger(int64_t val) {
    assert(val >= 0 && "value should be positive");
    init((uint64_t)val);
  }

  UBigInteger<SIZE> operator-() const {
    UBigInteger<SIZE> ret = *this;
    for (size_t i = 0; i < data.size(); ++i) {
      ret.data[i] = ~this->data[i];
    }
    ++ret;
    return ret;
  }

  UBigInteger<SIZE>& operator++() {
    // prefix operator
    for (size_t i = 0; i < data.size() && ++data[i] == 0; ++i) {
    }
    return *this;
  }

  UBigInteger<SIZE> operator++(int) {
    // postfix operator
    UBigInteger<SIZE> ret = *this;
    ++(*this);
    return ret;
  }

  UBigInteger<SIZE>& operator--() {
    // prefix operator
    for (size_t i = 0; i < data.size() && --data[i] == 0xff; ++i) {
    }
    return *this;
  }

  UBigInteger<SIZE> operator--(int) {
    UBigInteger<SIZE> ret = *this;
    --(*this);
    return ret;
  }

  UBigInteger<SIZE>& operator+=(const UBigInteger<SIZE>& b) {
    uint64_t carry = 0;
    for (size_t i = 0; i < data.size(); ++i) {
      uint64_t n = carry + this->data[i] + b.data[i];
      this->data[i] = n & 0xff;
      carry = n >> 8;
    }
    return *this;
  }

  UBigInteger<SIZE>& operator-=(const UBigInteger<SIZE>& b) {
    return *this += -UBigInteger(b);
  }

  UBigInteger<SIZE>& operator*=(const UBigInteger<SIZE>& b) {
    uint64_t carry = 0;
    for (size_t i = 0; i < data.size(); ++i) {
      for (size_t j = 0; j < data.size(); ++j) {
        uint64_t n = carry + this->data[i] * b.data[i];
        this->data[i] = n & 0xff;
        carry = n >> 8;
      }
    }
    return *this;
  }

  friend inline UBigInteger<SIZE> operator+(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    return UBigInteger<SIZE>(a) += b;
  }

  friend inline UBigInteger<SIZE> operator-(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    return UBigInteger<SIZE>(a) -= b;
  }

  friend inline UBigInteger<SIZE> operator*(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    return UBigInteger<SIZE>(a) *= b;
  }

  bool operator==(const UBigInteger<SIZE>& val) const {
    return this->data == val.data;
  }

  bool operator!=(const UBigInteger<SIZE>& val) const {
    return !(*this == val);
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const UBigInteger<SIZE>& b) const {
    for (int64_t i = (int64_t)(data.size() - 1); i != 0; --i) {
      if (this->data[i] < b.data[i]) {
        return -1;
      }
      if (this->data[i] > b.data[i]) {
        return 1;
      }
    }

    return 0;
  }

  friend bool operator>(const UBigInteger<SIZE>& a,
                        const UBigInteger<SIZE>& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const UBigInteger<SIZE>& a,
                        const UBigInteger<SIZE>& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const UBigInteger<SIZE>& a,
                         const UBigInteger<SIZE>& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const UBigInteger<SIZE>& a,
                         const UBigInteger<SIZE>& b) {
    return a.compareTo(b) <= 0;
  }

  friend std::string toPrettyString(const UBigInteger<SIZE>& val) {
    std::string ret = HexStr(val.data.rbegin(), val.data.rend());
    removeZeros(ret);
    return ret;
  }

 protected:
  template <typename T,
            typename = typename std::enable_if<
                std::is_integral<T>::value && std::is_unsigned<T>::value>::type>
  void init(T value) {
    size_t val_size = sizeof(value);
    assert(data.size() >= val_size && "data has a small size");
    for (size_t i = 0; i < data.size(); ++i) {
      if (i < val_size) {
        data[i] = (uint8_t)(value >> 8 * i);
      } else {
        data[i] = 0;
      }
    }
  }

 private:
  std::array<uint8_t, SIZE / 8> data{};
};

}  // namespace nnoops

#endif
