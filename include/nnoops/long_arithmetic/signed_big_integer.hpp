#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_SIGNED_BIG_INTEGER_HPP_

#include <stdlib.h>

#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

// Representation on the signed integer with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
template <uint64_t SIZE = 64, typename BASE_T = uint32_t>
struct BigInteger {
  using BigIntegerT = BigInteger<SIZE, BASE_T>;
  using UBigIntegerT = UBigInteger<SIZE, BASE_T>;

  ~BigInteger() = default;

  BigInteger() = default;

  BigInteger(const BigIntegerT& val) : sign(val.sign), value(val.value) {}

  BigInteger(BigIntegerT&& val)
      : sign(std::move(val.sign)), value(std::move(val.value)) {}

  BigIntegerT& operator=(const BigIntegerT& val) {
    this->sign = val.sign;
    this->value = val.value;
    return *this;
  }

  BigIntegerT& operator=(BigIntegerT&& val) {
    this->sign = std::move(val.sign);
    this->value = std::move(val.value);
    return *this;
  }

  BigInteger(const std::string& str, NumFormat format = NumFormat::DEC) {
    THROW_ARITH_ERROR(!str.empty(), "str value should not be empty");
    if (str[0] == '-') {
      this->sign = false;
    } else {
      this->sign = true;
    }
    this->value = UBigIntegerT(str.substr(1), format);
  }

  BigInteger(uint32_t val) : sign(true), value(val) {}

  BigInteger(uint64_t val) : sign(true), value(val) {}

  BigInteger(int32_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigInteger(int64_t val) : sign(val >= 0 ? true : false), value(abs(val)) {}

  BigIntegerT operator-() const {
    BigIntegerT ret = *this;
    if (ret.value != UBigIntegerT::zero_value()) {
      ret.sign = this->sign == true ? false : true;
    }
    return ret;
  }

  BigIntegerT& operator++() {
    // prefix operator
    if (sign == true) {
      ++value;
    } else {
      --value;
    }

    if (value == UBigIntegerT::zero_value()) {
      sign = true;
    }

    return *this;
  }

  BigIntegerT operator++(int) {
    // postfix operator
    BigIntegerT ret = *this;
    ++(*this);
    return ret;
  }

  BigIntegerT& operator--() {
    // prefix operator
    if (value == UBigIntegerT::zero_value()) {
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

  BigIntegerT operator--(int) {
    // postfix operator
    BigIntegerT ret = *this;
    --(*this);
    return ret;
  }

  BigIntegerT& operator+=(const BigIntegerT& b) {
    addition(*this, b, *this);
    return *this;
  }

  BigIntegerT& operator-=(const BigIntegerT& b) {
    substraction(*this, b, *this);
    return *this;
  }

  BigIntegerT& operator*=(const BigIntegerT& b) {
    BigIntegerT res;
    multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  BigIntegerT& operator/=(const BigIntegerT& b) {
    division(*this, b, *this);
    return *this;
  }

  BigIntegerT& operator%=(const BigIntegerT& b) {
    BigIntegerT q;
    division(*this, b, q, this);
    return *this;
  }

  friend inline BigIntegerT operator+(const BigIntegerT& a,
                                      const BigIntegerT& b) {
    BigIntegerT res;
    addition(a, b, res);
    return res;
  }

  friend inline BigIntegerT operator-(const BigIntegerT& a,
                                      const BigIntegerT& b) {
    BigIntegerT res;
    substraction(a, b, res);
    return res;
  }

  friend inline BigIntegerT operator*(const BigIntegerT& a,
                                      const BigIntegerT& b) {
    BigIntegerT res;
    multiplication(a, b, res);
    return res;
  }

  friend inline BigIntegerT operator/(const BigIntegerT& a, BigIntegerT& b) {
    BigIntegerT q;
    division(a, b, q);
    return q;
  }

  friend inline BigIntegerT operator%(const BigIntegerT& a,
                                      const BigIntegerT& b) {
    BigIntegerT q;
    BigIntegerT r;
    division(a, b, q, &r);
    return r;
  }

  bool operator==(const BigIntegerT& val) const {
    return this->sign == val.sign && this->value == val.value;
  }

  bool operator!=(const BigIntegerT& val) const { return !(*this == val); }

  friend bool operator>(const BigIntegerT& a, const BigIntegerT& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const BigIntegerT& a, const BigIntegerT& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const BigIntegerT& a, const BigIntegerT& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const BigIntegerT& a, const BigIntegerT& b) {
    return a.compareTo(b) <= 0;
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const BigIntegerT& b) const {
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
  friend void addition(const BigIntegerT& a,
                       const BigIntegerT& b,
                       BigIntegerT& result) {
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
    result.sign = result.value == UBigIntegerT::zero_value() ? true : sign;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void substraction(const BigIntegerT& a,
                           const BigIntegerT& b,
                           BigIntegerT& result) {
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
    result.sign = result.value == UBigIntegerT::zero_value() ? true : sign;
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void multiplication(const BigIntegerT& a,
                             const BigIntegerT& b,
                             BigIntegerT& result) {
    // x * y == x * y
    // x * (-y) == -(x * y)
    // (-x) * y == -(x * y)
    // (-x) * (-y) == x * y
    classical_multiplication(a.value, b.value, result.value);

    result.sign =
        result.value == UBigIntegerT::zero_value() ? true : a.sign == b.sign;
  }

  friend void division(const BigIntegerT& dividend,
                       const BigIntegerT& divisor,
                       BigIntegerT& quotient,
                       BigIntegerT* remainder = nullptr) {
    classical_division(dividend.value,
                       divisor.value,
                       quotient.value,
                       remainder != nullptr ? &remainder->value : nullptr);

    quotient.sign = quotient.value == UBigIntegerT::zero_value()
                        ? true
                        : dividend.sign == divisor.sign;

    if (remainder != nullptr) {
      remainder->sign =
          remainder->value == UBigIntegerT::zero_value() ? true : dividend.sign;
    }
  }

  static BigIntegerT min_value() {
    BigIntegerT ret;
    ret.value = UBigIntegerT::max_value();
    ret.sign = false;
    return ret;
  }

  static BigIntegerT max_value() {
    BigIntegerT ret;
    ret.value = UBigIntegerT::max_value();
    ret.sign = true;
    return ret;
  }

  static BigIntegerT zero_value() { return BigIntegerT(); }

  UBigIntegerT& get_unsigned() { return this->value; }

  const UBigIntegerT& get_unsigned() const { return this->value; }

  friend std::string toPrettyString(const BigIntegerT& val,
                                    NumFormat format = NumFormat::DEC) {
    if (val.sign == true) {
      return toPrettyString(val.value, format);
    } else {
      return "-" + toPrettyString(val.value, format);
    }
  }

 private:
  // sign == true means positive number
  // sign == false means negative number
  bool sign = true;
  // unsigned value
  UBigInteger<SIZE, BASE_T> value;
};

extern template struct BigInteger<8, uint8_t>;
extern template struct BigInteger<16, uint8_t>;
extern template struct BigInteger<32, uint8_t>;
extern template struct BigInteger<64, uint8_t>;
extern template struct BigInteger<128, uint8_t>;
extern template struct BigInteger<256, uint8_t>;
extern template struct BigInteger<512, uint8_t>;
extern template struct BigInteger<1024, uint8_t>;
extern template struct BigInteger<2048, uint8_t>;
extern template struct BigInteger<4096, uint8_t>;

extern template struct BigInteger<16, uint16_t>;
extern template struct BigInteger<32, uint16_t>;
extern template struct BigInteger<64, uint16_t>;
extern template struct BigInteger<128, uint16_t>;
extern template struct BigInteger<256, uint16_t>;
extern template struct BigInteger<512, uint16_t>;
extern template struct BigInteger<1024, uint16_t>;
extern template struct BigInteger<2048, uint16_t>;
extern template struct BigInteger<4096, uint16_t>;

extern template struct BigInteger<32, uint32_t>;
extern template struct BigInteger<64, uint32_t>;
extern template struct BigInteger<128, uint32_t>;
extern template struct BigInteger<256, uint32_t>;
extern template struct BigInteger<512, uint32_t>;
extern template struct BigInteger<1024, uint32_t>;
extern template struct BigInteger<2048, uint32_t>;
extern template struct BigInteger<4096, uint32_t>;

}  // namespace nnoops

#endif
