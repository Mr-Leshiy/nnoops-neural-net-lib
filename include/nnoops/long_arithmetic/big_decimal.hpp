#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_

#include <math.h>
#include <stdint.h>

#include <string>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"

namespace nnoops {

// Representation on the big decimal with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
// actual size of the BigDecimal equals to SIZE / 2
// representation is equal to quotient of a / b
template <uint64_t SIZE = 64, typename BASE_T = uint32_t>
struct BigDecimal {
  using BigDecimalT = BigDecimal<SIZE, BASE_T>;
  using BigIntegerT = BigInteger<SIZE, BASE_T>;

  ~BigDecimal() = default;

  BigDecimal() = default;

  BigDecimal(const BigDecimalT& val)
      : exponent(val.exponent), mantissa(val.mantissa) {}

  BigDecimal(BigDecimalT&& val)
      : exponent(std::move(val.exponent)), mantissa(std::move(val.mantissa)) {}

  BigDecimalT& operator=(const BigDecimalT& val) {
    this->exponent = val.exponent;
    this->mantissa = val.mantissa;
    return *this;
  }

  BigDecimalT& operator=(BigDecimalT&& val) {
    this->exponent = std::move(val.exponent);
    this->mantissa = std::move(val.mantissa);
    return *this;
  }

  BigDecimal(std::string str, NumFormat format = NumFormat::DEC) {
    THROW_ARITH_ERROR(!str.empty(), "str value should not be empty");
    bool sign = true;
    if (str[0] == '-') {
      str = str.substr(1);
      sign = false;
    }
    // find '.' and remove it
    int64_t position = (int64_t)str.find('.');
    size_t str_size = str.size();
    str = str.substr(0, position) + str.substr(position + 1, str_size - 1);
    if (format == NumFormat::HEX) {
      str = HexToDec(str);
    }
    // remove zeros at the end of the number
    size_t i = str.size() - 1;
    for (; i != 0 && str[i] == '0'; --i) {
    }
    str.erase(i + 1);
    for (i = 0; i < str.size() && str[i] == '0'; ++i, --position) {
    }

    this->mantissa =
        BigIntegerT(std::string(str.begin() + i, str.end()), NumFormat::DEC);
    this->mantissa.setSign(sign);
    this->exponent = position;
  }

  BigDecimal(int8_t val) { init(val); }

  BigDecimal(int16_t val) { init(val); }

  BigDecimal(int32_t val) { init(val); }

  BigDecimal(int64_t val) { init(val); }

  BigDecimalT& operator+=(const BigDecimalT& b) {
    addition(*this, b, *this);
    return *this;
  }

  BigDecimalT& operator-=(const BigDecimalT& b) {
    substraction(*this, b, *this);
    return *this;
  }

  BigDecimalT& operator*=(const BigDecimalT& b) {
    BigDecimalT res;
    multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  BigDecimalT& operator/=(const BigDecimalT& b) {
    division(*this, b, *this);
    return *this;
  }

  friend inline BigDecimalT operator+(const BigDecimalT& a,
                                      const BigDecimalT& b) {
    BigDecimalT res;
    addition(a, b, res);
    return res;
  }

  friend inline BigDecimalT operator-(const BigDecimalT& a,
                                      const BigDecimalT& b) {
    BigDecimalT res;
    substraction(a, b, res);
    return res;
  }

  friend inline BigDecimalT operator*(const BigDecimalT& a,
                                      const BigDecimalT& b) {
    BigDecimalT res;
    multiplication(a, b, res);
    return res;
  }

  friend inline BigDecimalT operator/(const BigDecimalT& a,
                                      const BigDecimalT& b) {
    BigDecimalT q;
    division(a, b, q);
    return q;
  }

  bool operator==(const BigDecimalT& val) const {
    return this->mantissa == val.mantissa && this->exponent == val.exponent;
  }

  bool operator!=(const BigDecimalT& val) const { return !(*this == val); }

  friend bool operator>(const BigDecimalT& a, const BigDecimalT& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const BigDecimalT& a, const BigDecimalT& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const BigDecimalT& a, const BigDecimalT& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const BigDecimalT& a, const BigDecimalT& b) {
    return a.compareTo(b) <= 0;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void addition(const BigDecimalT& a,
                       const BigDecimalT& b,
                       BigDecimalT& result) {
    (void)a;
    (void)b;
    (void)result;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void substraction(const BigDecimalT& a,
                           const BigDecimal& b,
                           BigDecimalT& result) {
    (void)a;
    (void)b;
    (void)result;
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void multiplication(const BigDecimalT& a,
                             const BigDecimalT& b,
                             BigDecimalT& result) {
    addition(a.exponent, b.exponent, result.exponent);
    multiplication(a.mantissa, b.mantissa, result.mantissa);
  }

  friend void division(BigDecimalT dividend,
                       BigDecimalT divisor,
                       BigDecimalT& quotient) {
    (void)dividend;
    (void)divisor;
    (void)quotient;
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const BigDecimalT& val) const {
    int rv = this->exponent.compareTo(val.exponent);
    if (rv != 0) {
      return rv;
    }

    return this->mantissa.compareTo(val.mantissa);
  }

  friend std::string toPrettyString(const BigDecimalT& val,
                                    NumFormat format = NumFormat::DEC) {
    std::string m_part = toPrettyString(val.mantissa, format);
    if (m_part[0] == '-') {
      return "-0." + m_part.substr(1) + "*e^(" +
             toPrettyString(val.exponent, format) + ")";
    }

    return "0." + m_part + "*e^(" + toPrettyString(val.exponent, format) + ")";
  }

 private:
  template <
      typename T,
      typename = typename std::enable_if<std::is_integral<T>::value>::type>
  void init(T val) {
    uint64_t exp = 0;
    while (val % 10 == 0) {
      val /= 10;
      ++exp;
    }
    this->mantissa = val;
    while (val != 0) {
      val /= 10;
      ++exp;
    }
    this->exponent = exp;
  }

 private:
  BigIntegerT exponent{};
  BigIntegerT mantissa{};
};

}  // namespace nnoops

#endif
