#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_UNSIGNED_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_UNSIGNED_BIG_INTEGER_HPP_

#include <stdint.h>

#include <algorithm>
#include <array>
#include <limits>
#include <string>
#include <type_traits>

#include "nnoops/long_arithmetic/arith_error.hpp"
#include "nnoops/strutil.hpp"

namespace nnoops {

// Representation on the unsigned integer with the arbitrary size
// SIZE should be multiple of 32 (1 byte)
template <uint64_t SIZE = 64,
          typename base_t = uint32_t,
          typename = typename std::enable_if<
              (SIZE != 0 && SIZE % (sizeof(base_t) * 8) == 0) &&
              (std::is_integral<base_t>::value &&
               std::is_unsigned<base_t>::value)>::type>
struct UBigInteger {
  ~UBigInteger() = default;

  UBigInteger() {
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      this->data[i] = 0;
    }
  };

  UBigInteger(const UBigInteger<SIZE, base_t>& val) : data(val.data) {}

  UBigInteger(UBigInteger<SIZE, base_t>&& val) : data(std::move(val.data)) {}

  UBigInteger<SIZE, base_t>& operator=(const UBigInteger<SIZE, base_t>& val) {
    this->data = val.data;
    return *this;
  }

  UBigInteger<SIZE, base_t>& operator=(UBigInteger<SIZE, base_t>&& val) {
    this->data = std::move(val.data);
    return *this;
  }

  UBigInteger(uint8_t val) { init(val); }

  UBigInteger(uint16_t val) { init(val); }

  UBigInteger(uint32_t val) { init(val); }

  UBigInteger(uint64_t val) { init(val); }

  UBigInteger(int8_t val) {
    THROW_ARITH_ERROR(val >= 0, "negative value, value should be positive");
    init((uint8_t)val);
  }

  UBigInteger(int16_t val) {
    THROW_ARITH_ERROR(val >= 0, "negative value, value should be positive");
    init((uint16_t)val);
  }

  UBigInteger(int32_t val) {
    THROW_ARITH_ERROR(val >= 0, "negative value, value should be positive");
    init((uint32_t)val);
  }

  UBigInteger(int64_t val) {
    THROW_ARITH_ERROR(val >= 0, "negative value, value should be positive");
    init((uint64_t)val);
  }

  UBigInteger<SIZE, base_t>& operator++() {
    // prefix operator
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      if (++data[i] != 0) {
        break;
      } else {
        THROW_ARITH_ERROR(
            i != ARRAY_LEN - 1,
            "increment overflow",
            "result should be in the interval [0, UBigInteger::max_value()]");
      }
    }
    return *this;
  }

  UBigInteger<SIZE, base_t> operator++(int) {
    // postfix operator
    UBigInteger<SIZE, base_t> ret = *this;
    ++(*this);
    return ret;
  }

  UBigInteger<SIZE, base_t>& operator--() {
    // prefix operator
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      if (--data[i] != BASE) {
        break;
      } else {
        THROW_ARITH_ERROR(
            i != ARRAY_LEN - 1,
            "decrement overflow",
            "result should be in the interval [0, UBigInteger::max_value()]");
      }
    }
    return *this;
  }

  UBigInteger<SIZE, base_t> operator--(int) {
    UBigInteger<SIZE, base_t> ret = *this;
    --(*this);
    return ret;
  }

  UBigInteger<SIZE, base_t>& operator+=(const UBigInteger<SIZE, base_t>& b) {
    classical_addition(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE, base_t>& operator-=(const UBigInteger<SIZE, base_t>& b) {
    classical_substraction(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE, base_t>& operator*=(const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> res;
    classical_multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  UBigInteger<SIZE, base_t>& operator/=(const UBigInteger<SIZE, base_t>& b) {
    classical_division(*this, b, *this);
    return *this;
  }

  UBigInteger<SIZE, base_t>& operator%=(const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> q;
    classical_division(*this, b, q, this);
    return *this;
  }

  friend inline UBigInteger<SIZE, base_t> operator+(
      const UBigInteger<SIZE, base_t>& a, const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> res;
    classical_addition(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE, base_t> operator-(
      const UBigInteger<SIZE, base_t>& a, const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> res;
    classical_substraction(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE, base_t> operator*(
      const UBigInteger<SIZE, base_t>& a, const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> res;
    classical_multiplication(a, b, res);
    return res;
  }

  friend inline UBigInteger<SIZE, base_t> operator/(
      const UBigInteger<SIZE, base_t>& a, const UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> q;
    classical_division(a, b, q);
    return q;
  }

  friend inline UBigInteger<SIZE, base_t> operator%(
      const UBigInteger<SIZE, base_t>& a, UBigInteger<SIZE, base_t>& b) {
    UBigInteger<SIZE, base_t> q;
    UBigInteger<SIZE, base_t> r;
    classical_division(a, b, q, &r);
    return r;
  }

  bool operator==(const UBigInteger<SIZE, base_t>& val) const {
    return this->data == val.data;
  }

  bool operator!=(const UBigInteger<SIZE, base_t>& val) const {
    return !(*this == val);
  }

  friend bool operator>(const UBigInteger<SIZE, base_t>& a,
                        const UBigInteger<SIZE, base_t>& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const UBigInteger<SIZE, base_t>& a,
                        const UBigInteger<SIZE, base_t>& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const UBigInteger<SIZE, base_t>& a,
                         const UBigInteger<SIZE, base_t>& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const UBigInteger<SIZE, base_t>& a,
                         const UBigInteger<SIZE, base_t>& b) {
    return a.compareTo(b) <= 0;
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const UBigInteger<SIZE, base_t>& b) const {
    for (uint64_t i = ARRAY_LEN - 1;; --i) {
      if (this->data[i] < b.data[i]) {
        return -1;
      }
      if (this->data[i] > b.data[i]) {
        return 1;
      }
      if (i == 0) {
        break;
      }
    }

    return 0;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_addition(const UBigInteger<SIZE, base_t>& a,
                                 const UBigInteger<SIZE, base_t>& b,
                                 UBigInteger<SIZE, base_t>& result) {
    uint64_t carry = 0;
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      uint64_t n = carry + a.data[i] + b.data[i];
      result.data[i] = n & BASE;  // same to the n % (BASE + 1)
      carry = n >> BASE_BITS;     // same to the [n / (BASE + 1)]
    }
    THROW_ARITH_ERROR(
        carry == 0,
        "addition overflow",
        "result should be in the interval [0, UBigInteger::max_value()]");
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_substraction(const UBigInteger<SIZE, base_t>& a,
                                     const UBigInteger<SIZE, base_t>& b,
                                     UBigInteger<SIZE, base_t>& result) {
    int64_t carry = 0;
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      int64_t n = carry + a.data[i] - b.data[i];
      result.data[i] = n % ((uint64_t)BASE + 1);
      carry = n >= 0 ? 0 : -1;  // same to the [n / (BASE + 1)]
    }
    THROW_ARITH_ERROR(
        carry == 0,
        "substraction overflow",
        "result should be in the interval [0, UBigInteger::max_value()]");
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void classical_multiplication(const UBigInteger<SIZE, base_t>& a,
                                       const UBigInteger<SIZE, base_t>& b,
                                       UBigInteger<SIZE, base_t>& result) {
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      uint64_t carry = 0;
      for (size_t j = 0; i + j < ARRAY_LEN; ++j) {
        uint64_t n =
            carry + result.data[i + j] + (uint64_t)a.data[i] * b.data[j];
        result.data[i + j] = n & BASE;
        carry = n >> BASE_BITS;
      }
      THROW_ARITH_ERROR(
          carry == 0,
          "multiplication overflow",
          "result should be in the interval [0, UBigInteger::max_value()]");
    }
  }

  friend void classical_division(
      UBigInteger<SIZE, base_t> dividend,
      UBigInteger<SIZE, base_t> divisor,
      UBigInteger<SIZE, base_t>& quotient,
      UBigInteger<SIZE, base_t>* remainder = nullptr) {
    THROW_ARITH_ERROR(divisor != (UBigInteger<SIZE, base_t>::zero_value()),
                      "devide by zero");

    quotient = UBigInteger<SIZE, base_t>::zero_value();

    if (divisor > dividend) {
      if (remainder != nullptr) {
        *remainder = dividend;
      }
      return;
    }

    uint64_t m = 0, n = 0;
    for (size_t i = ARRAY_LEN - 1;; --i) {
      if (divisor.data[i] != 0 && n == 0) {
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

    for (int64_t j = m;; --j) {
      // Calculate q
      uint64_t el1 =
          j + n + 1 >= ARRAY_LEN
              ? dividend.data[j + n]
              : (uint64_t)(dividend.data[j + n + 1] * ((uint64_t)BASE + 1)) +
                    dividend.data[j + n];

      uint64_t r = el1 % divisor.data[n];
      uint64_t q = el1 / divisor.data[n];

      // Test
      while (q == (BASE + 1) ||
             (n >= 1 && q * divisor.data[n - 1] >
                            ((BASE + 1) * r + dividend.data[j + n - 1]))) {
        --q;
        r += divisor.data[n];
        if (r > BASE) {
          break;
        }
      }

      // Multiply and substract
      UBigInteger<SIZE, base_t> tmp1;
      for (size_t i = j, k = 0; i <= j + n + 1 && i < ARRAY_LEN; ++i, ++k) {
        tmp1.data[k] = dividend.data[i];
      }

      UBigInteger<SIZE, base_t> tmp2 = (base_t)q * divisor;

      // Test reminder
      if (tmp1 >= tmp2) {
        tmp1 -= tmp2;
        quotient.data[j] = q;
      } else {
        tmp1 -= tmp2;
        quotient.data[j] = q - 1;
        tmp1 += divisor;
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

  static UBigInteger<SIZE, base_t> min_value() {
    return UBigInteger<SIZE, base_t>();
  }

  static UBigInteger<SIZE, base_t> max_value() {
    UBigInteger<SIZE, base_t> ret;
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      ret.data[i] = BASE;
    }
    return ret;
  }

  static UBigInteger<SIZE, base_t> zero_value() {
    return UBigInteger<SIZE, base_t>();
  }

  friend std::string toPrettyString(const UBigInteger<SIZE, base_t>& val) {
    return removeZeros(HexStr(val.data.rbegin(), val.data.rend()));
  }

 private:
  template <typename T,
            typename = typename std::enable_if<
                std::is_integral<T>::value && std::is_unsigned<T>::value>::type>
  void init(T value) {
    static constexpr const size_t val_size =
        sizeof(T) * 8 / BASE_BITS > 0 ? sizeof(T) * 8 / BASE_BITS : 1;

    THROW_ARITH_ERROR(ARRAY_LEN >= val_size, "data has a small size");
    for (size_t i = 0; i < ARRAY_LEN; ++i) {
      if (i < val_size) {
        data[i] = (base_t)(value >> BASE_BITS * i);
      } else {
        data[i] = 0;
      }
    }
  }

  static constexpr const base_t BASE = std::numeric_limits<base_t>::max();
  static constexpr const uint8_t BASE_BITS = sizeof(base_t) * 8;
  static constexpr const uint64_t ARRAY_LEN = SIZE / BASE_BITS;
  std::array<base_t, ARRAY_LEN> data{};
};

extern template struct UBigInteger<8, uint8_t>;
extern template struct UBigInteger<16, uint8_t>;
extern template struct UBigInteger<32, uint8_t>;
extern template struct UBigInteger<64, uint8_t>;
extern template struct UBigInteger<128, uint8_t>;
extern template struct UBigInteger<256, uint8_t>;
extern template struct UBigInteger<512, uint8_t>;
extern template struct UBigInteger<1024, uint8_t>;
extern template struct UBigInteger<2048, uint8_t>;
extern template struct UBigInteger<4096, uint8_t>;

extern template struct UBigInteger<32, uint32_t>;
extern template struct UBigInteger<64, uint32_t>;
extern template struct UBigInteger<128, uint32_t>;
extern template struct UBigInteger<256, uint32_t>;
extern template struct UBigInteger<512, uint32_t>;
extern template struct UBigInteger<1024, uint32_t>;
extern template struct UBigInteger<2048, uint32_t>;
extern template struct UBigInteger<4096, uint32_t>;

}  // namespace nnoops

#endif
