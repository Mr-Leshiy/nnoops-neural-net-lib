#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_

#include <stdlib.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

// Representation on the signed integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64,
          typename = typename std::enable_if<SIZE % 8 == 0 && SIZE != 0>::type>
struct BigInteger {
  ~BigInteger() = default;

  BigInteger() = default;

  BigInteger(const BigInteger<SIZE>& val) : sign(val.sign), value(val.value) {}

  BigInteger(BigInteger<SIZE>&& val)
      : sign(std::move(val.sign)), value(std::move(val.value)) {}

  BigInteger<SIZE>& operator=(const BigInteger<SIZE>& val) {
    this->sign = val.sign;
    this->value = val.value;
    return *this;
  }

  BigInteger<SIZE>& operator=(BigInteger<SIZE>&& val) {
    this->sign = std::move(val.sign);
    this->value = std::move(val.value);
    return *this;
  }

  BigInteger(uint8_t val) : sign(true), value(val) {}

  BigInteger(uint16_t val) : sign(true), value(val) {}

  BigInteger(uint32_t val) : sign(true), value(val) {}

  BigInteger(uint64_t val) : sign(true), value(val) {}

  BigInteger(int8_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigInteger(int16_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigInteger(int32_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigInteger(int64_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigInteger<SIZE> operator-() const {
    BigInteger<SIZE> ret = *this;
    if (ret.value != UBigInteger<SIZE>::zero_value()) {
      ret.sign = this->sign == true ? false : true;
    }
    return ret;
  }

  BigInteger<SIZE>& operator++() {
    // prefix operator
    if (sign == true) {
      ++value;
    } else {
      --value;
    }

    if (value == UBigInteger<SIZE>::zero_value()) {
      sign = true;
    }

    return *this;
  }

  BigInteger<SIZE> operator++(int) {
    // postfix operator
    BigInteger<SIZE> ret = *this;
    ++(*this);
    return ret;
  }

  BigInteger<SIZE>& operator--() {
    // prefix operator
    if (value == UBigInteger<SIZE>::zero_value()) {
      this->sign = false;
      ++value;
      return *this;
    }
    if (sign == true) {
      --value;
    } else {
      ++value;
    }
    return *this;
  }

  BigInteger<SIZE> operator--(int) {
    // postfix operator
    BigInteger<SIZE> ret = *this;
    --(*this);
    return ret;
  }

  BigInteger<SIZE>& operator+=(const BigInteger<SIZE>& b) {
    classical_addition(*this, b, *this);
    return *this;
  }

  BigInteger<SIZE>& operator-=(const BigInteger<SIZE>& b) {
    classical_substraction(*this, b, *this);
    return *this;
  }

  BigInteger<SIZE>& operator*=(const BigInteger<SIZE>& b) {
    BigInteger<SIZE> res;
    classical_multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  BigInteger<SIZE>& operator/=(const BigInteger<SIZE>& b) {
    classical_division(*this, b, *this);
    return *this;
  }

  BigInteger<SIZE>& operator%=(const BigInteger<SIZE>& b) {
    BigInteger<SIZE> q;
    classical_division(*this, b, q, this);
    return *this;
  }

  friend inline BigInteger<SIZE> operator+(const BigInteger<SIZE>& a,
                                           const BigInteger<SIZE>& b) {
    BigInteger<SIZE> res;
    classical_addition(a, b, res);
    return res;
  }

  friend inline BigInteger<SIZE> operator-(const BigInteger<SIZE>& a,
                                           const BigInteger<SIZE>& b) {
    BigInteger<SIZE> res;
    classical_substraction(a, b, res);
    return res;
  }

  friend inline BigInteger<SIZE> operator*(const BigInteger<SIZE>& a,
                                           const BigInteger<SIZE>& b) {
    BigInteger<SIZE> res;
    classical_multiplication(a, b, res);
    return res;
  }

  friend inline BigInteger<SIZE> operator/(const BigInteger<SIZE>& a,
                                           BigInteger<SIZE>& b) {
    BigInteger<SIZE> q;
    classical_division(a, b, q);
    return q;
  }

  friend inline BigInteger<SIZE> operator%(const BigInteger<SIZE>& a,
                                           const BigInteger<SIZE>& b) {
    BigInteger<SIZE> q;
    BigInteger<SIZE> r;
    classical_division(a, b, q, &r);
    return r;
  }

  bool operator==(const BigInteger<SIZE>& val) const {
    return this->sign == val.sign && this->value == val.value;
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

    return b.sign == false ? -1 * value.compareTo(b.value)
                           : value.compareTo(b.value);
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_addition(const BigInteger<SIZE>& a,
                                 const BigInteger<SIZE>& b,
                                 BigInteger<SIZE>& result) {
    bool sign = a.sign;
    if (a.sign == b.sign) {
      // a + b == a + b
      // (-a) + (-b) == -(a + b)
      classical_addition(a.value, b.value, result.value);
    } else {
      // a + (-y) == x - y == -(y - x)
      // (-x) + y == y - x == -(x - y)
      if (a.value >= b.value) {
        classical_substraction(a.value, b.value, result.value);
      } else {
        sign = !sign;
        classical_substraction(b.value, a.value, result.value);
      }
    }

    // 0 has the positive sign
    result.sign = result.value == UBigInteger<SIZE>::zero_value() ? true : sign;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void classical_substraction(const BigInteger<SIZE>& a,
                                     const BigInteger<SIZE>& b,
                                     BigInteger<SIZE>& result) {
    bool sign = a.sign;
    if (a.sign != b.sign) {
      // a - (-b) == a + b
      // (-a) - b == -(a + b)
      classical_addition(a.value, b.value, result.value);
    } else {
      // a - b == -(b - a)
      // (-a) - (-b) == b - a == -(a - b)
      if (a.value >= b.value) {
        classical_substraction(a.value, b.value, result.value);
      } else {
        sign = !sign;
        classical_substraction(b.value, a.value, result.value);
      }
    }

    // 0 has the positive sign
    result.sign = result.value == UBigInteger<SIZE>::zero_value() ? true : sign;
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void classical_multiplication(const BigInteger<SIZE>& a,
                                       const BigInteger<SIZE>& b,
                                       BigInteger<SIZE>& result) {
    // x * y == x * y
    // x * (-y) == -(x * y)
    // (-x) * y == -(x * y)
    // (-x) * (-y) == x * y
    classical_multiplication(a.value, b.value, result.value);

    result.sign = result.value == UBigInteger<SIZE>::zero_value()
                      ? true
                      : a.sign == b.sign;
  }

  friend void classical_division(const BigInteger<SIZE>& dividend,
                                 const BigInteger<SIZE>& divisor,
                                 BigInteger<SIZE>& quotient,
                                 BigInteger<SIZE>* remainder = nullptr) {
    classical_division(dividend.value,
                       divisor.value,
                       quotient.value,
                       remainder != nullptr ? &remainder->value : nullptr);

    quotient.sign = quotient.value == UBigInteger<SIZE>::zero_value()
                        ? true
                        : dividend.sign == divisor.sign;

    if (remainder != nullptr) {
      remainder->sign = remainder->value == UBigInteger<SIZE>::zero_value()
                            ? true
                            : dividend.sign;
    }
  }

  static BigInteger<SIZE> min_value() {
    BigInteger<SIZE> ret;
    ret.value = UBigInteger<SIZE>::max_value();
    ret.sign = false;
    return ret;
  }

  static BigInteger<SIZE> max_value() {
    BigInteger<SIZE> ret;
    ret.value = UBigInteger<SIZE>::max_value();
    ret.sign = true;
    return ret;
  }

  static BigInteger<SIZE> zero_value() { return BigInteger<SIZE>(); }

  UBigInteger<SIZE>& get_unsigned() { return this->value; }

  const UBigInteger<SIZE>& get_unsigned() const { return this->value; }

  friend std::string toPrettyString(const BigInteger<SIZE>& val) {
    if (val.sign == true) {
      return toPrettyString(val.value);
    } else {
      return "-" + toPrettyString(val.value);
    }
  }

 private:
  // sign == true means positive number
  // sign == false means negative number
  bool sign = true;
  // unsigned value
  UBigInteger<SIZE> value;
};

extern template struct BigInteger<8>;
extern template struct BigInteger<16>;
extern template struct BigInteger<32>;
extern template struct BigInteger<64>;
extern template struct BigInteger<128>;
extern template struct BigInteger<256>;
extern template struct BigInteger<512>;
extern template struct BigInteger<1024>;
extern template struct BigInteger<2048>;
extern template struct BigInteger<4096>;

}  // namespace nnoops

#endif
