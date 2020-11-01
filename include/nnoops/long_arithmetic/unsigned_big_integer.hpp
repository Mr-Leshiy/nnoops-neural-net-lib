#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_UNSIGNED_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_UNSIGNED_BIG_INTEGER_HPP_

#include <stdint.h>

#include <array>
#include <cassert>
#include <string>
#include <type_traits>

#include "nnoops/long_arithmetic/arith_error.hpp"
#include "nnoops/strutil.hpp"

namespace nnoops {

// Representation on the unsigned integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct UBigInteger {
  virtual ~UBigInteger() = default;

  UBigInteger() noexcept {
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      this->data[i] = 0;
    }
  };

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
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      ret.data[i] = ~this->data[i];
    }
    ++ret;
    return ret;
  }

  UBigInteger<SIZE>& operator++() {
    // prefix operator
    for (size_t i = 0; i < ARRAY_LEN && ++data[i] == 0; ++i) {
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
    for (size_t i = 0; i < ARRAY_LEN && --data[i] == BASE; ++i) {
    }
    return *this;
  }

  UBigInteger<SIZE> operator--(int) {
    UBigInteger<SIZE> ret = *this;
    --(*this);
    return ret;
  }

  UBigInteger<SIZE>& operator+=(const UBigInteger<SIZE>& b) {
    classical_addition(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE>& operator-=(const UBigInteger<SIZE>& b) {
    classical_substraction(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE>& operator*=(const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> res;
    classical_multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  UBigInteger<SIZE>& operator/=(const UBigInteger<SIZE>& b) {
    classical_division(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE>& operator%=(const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> q;
    classical_division(*this, b, q, this);
    return *this;
  }

  friend inline UBigInteger<SIZE> operator+(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> res;
    classical_addition(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE> operator-(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> res;
    classical_substraction(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE> operator*(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> res;
    classical_multiplication(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE> operator/(const UBigInteger<SIZE>& a,
                                            const UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> q;
    classical_division(a, b, q);
    return q;
  }

  friend inline UBigInteger<SIZE> operator%(const UBigInteger<SIZE>& a,
                                            UBigInteger<SIZE>& b) {
    UBigInteger<SIZE> q;
    UBigInteger<SIZE> r;
    classical_division(a, b, q, &r);
    return r;
  }

  bool operator==(const UBigInteger<SIZE>& val) const {
    return this->data == val.data;
  }

  bool operator!=(const UBigInteger<SIZE>& val) const {
    return !(*this == val);
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

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const UBigInteger<SIZE>& b) const {
    for (int64_t i = (int64_t)(ARRAY_LEN - 1); i != 0; --i) {
      if (this->data[i] < b.data[i]) {
        return -1;
      }
      if (this->data[i] > b.data[i]) {
        return 1;
      }
    }

    return 0;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_addition(const UBigInteger<SIZE>& a,
                                 const UBigInteger<SIZE>& b,
                                 UBigInteger<SIZE>& result) {
    uint64_t carry = 0;
    for (size_t i = 0; i < UBigInteger<SIZE>::ARRAY_LEN; ++i) {
      uint64_t n = carry + a.data[i] + b.data[i];
      result.data[i] = n & UBigInteger<SIZE>::BASE;
      carry = n >> 8;
    }
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_substraction(const UBigInteger<SIZE>& a,
                                     const UBigInteger<SIZE>& b,
                                     UBigInteger<SIZE>& result) {
    uint64_t carry = 0;
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      uint64_t n = carry + a.data[i] - b.data[i];
      result.data[i] = n & BASE;
      carry = n >> 8;
    }
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void classical_multiplication(const UBigInteger<SIZE>& a,
                                       const UBigInteger<SIZE>& b,
                                       UBigInteger<SIZE>& result) {
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      uint64_t carry = 0;
      for (size_t j = 0; i + j < ARRAY_LEN; ++j) {
        uint64_t n =
            carry + result.data[i + j] + (uint64_t)(a.data[i] * b.data[j]);
        result.data[i + j] = n & BASE;
        carry = n >> 8;
      }
    }
  }

  friend void classical_division(UBigInteger<SIZE> dividend,
                                 UBigInteger<SIZE> divisor,
                                 UBigInteger<SIZE>& quotient,
                                 UBigInteger<SIZE>* remainder = nullptr) {
    if (divisor == 0) {
      throw arith_error("devide by zero");
    }

    quotient = 0;

    if (divisor > dividend) {
      if (remainder != nullptr) {
        *remainder = dividend;
      }
      return;
    }

    uint64_t m = 0, n = 0, d = 0;
    for (size_t i = ARRAY_LEN - 1;; --i) {
      if (divisor.data[i] != 0 && n == 0) {
        d = divisor.data[i];
        n = i;
      }

      if (dividend.data[i] != 0 && m == 0) {
        m = i;
      }

      if ((m != 0 && n != 0) || i == 0) {
        break;
      }
    }

    m -= n;

    // Normalize
    if (remainder == nullptr) {
      d = BASE / d;
      if (d != 1) {
        dividend *= d;
        divisor *= d;
      }
    }

    for (int64_t j = m;; --j) {
      // Calculate q
      uint64_t el1 =
          j + n + 1 >= ARRAY_LEN
              ? dividend.data[j + n]
              : (uint64_t)(dividend.data[j + n + 1] * (uint64_t)(BASE + 1)) +
                    dividend.data[j + n];
      uint64_t r = el1 % divisor.data[n];
      uint64_t q = el1 / divisor.data[n];

      // Test
      if (q == (BASE + 1) ||
          (n >= 1 && q * divisor.data[n - 1] >
                         ((BASE + 1) * r + dividend.data[j + n - 1]))) {
        while (r <= BASE) {
          ++q;
          r += divisor.data[n];
        }
      }

      // Multiply and substract
      UBigInteger<SIZE> tmp1 = 0;
      for (size_t i = j, k = 0; i <= j + n + 1 && i < ARRAY_LEN; ++i, ++k) {
        tmp1.data[k] = dividend.data[i];
      }

      auto tmp2 = q * divisor;

      // Test reminder
      if (tmp1 >= tmp2) {
        tmp1 -= tmp2;
        quotient.data[j] = q;
      } else {
        tmp1 -= tmp2 - divisor;
        quotient.data[j] = q - 1;
      }

      for (size_t i = j, k = 0; i <= j + n + 1 && i < ARRAY_LEN; ++i, ++k) {
        dividend.data[i] = tmp1.data[k];
      }

      if (j == 0) {
        break;
      }
    }

    if (remainder != nullptr) {
      *remainder = dividend;
    }
  }

  static UBigInteger<SIZE> min_value() { return UBigInteger<SIZE>(); }

  static UBigInteger<SIZE> max_value() {
    UBigInteger<SIZE> ret;
    return --ret;
  }

  static UBigInteger<SIZE> zero_value() { return UBigInteger<SIZE>(); }

  friend std::string toPrettyString(const UBigInteger<SIZE>& val) {
    return HexStr(val.data.rbegin(), val.data.rend());
  }

 protected:
  template <typename T,
            typename = typename std::enable_if<
                std::is_integral<T>::value && std::is_unsigned<T>::value>::type>
  void init(T value) {
    size_t val_size = sizeof(value);
    assert(ARRAY_LEN >= val_size && "data has a small size");
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      if (i < val_size) {
        data[i] = (uint8_t)(value >> 8 * i);
      } else {
        data[i] = 0;
      }
    }
  }

  static const uint8_t BASE = 0xff;
  static constexpr uint64_t ARRAY_LEN = SIZE / 8;
  std::array<uint8_t, SIZE / 8> data{};
};

extern template struct UBigInteger<8>;
extern template struct UBigInteger<16>;
extern template struct UBigInteger<32>;
extern template struct UBigInteger<64>;
extern template struct UBigInteger<128>;
extern template struct UBigInteger<256>;
extern template struct UBigInteger<512>;
extern template struct UBigInteger<1024>;

}  // namespace nnoops

#endif
