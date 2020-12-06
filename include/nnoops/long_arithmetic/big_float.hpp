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
struct BigFloat {
  using BigFloatT = BigFloat<SIZE, BASE_T>;
  using BigIntegerT = BigInteger<SIZE, BASE_T>;

  ~BigFloat() = default;

  BigFloat() = default;

  BigFloat(const BigFloatT& val)
      : exponent(val.exponent), mantissa(val.mantissa) {}

  BigFloat(BigFloatT&& val)
      : exponent(std::move(val.exponent)), mantissa(std::move(val.mantissa)) {}

  BigFloatT& operator=(const BigFloatT& val) {
    this->exponent = val.exponent;
    this->mantissa = val.mantissa;
    return *this;
  }

  BigFloatT& operator=(BigFloatT&& val) {
    this->exponent = std::move(val.exponent);
    this->mantissa = std::move(val.mantissa);
    return *this;
  }

  BigFloat(std::string str, NumFormat format = NumFormat::DEC) {
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

  BigFloat(int8_t val) { init(val); }

  BigFloat(int16_t val) { init(val); }

  BigFloat(int32_t val) { init(val); }

  BigFloat(int64_t val) { init(val); }

  BigFloatT& operator+=(const BigFloatT& b) {
    addition(*this, b, *this);
    return *this;
  }

  BigFloatT& operator-=(const BigFloatT& b) {
    substraction(*this, b, *this);
    return *this;
  }

  BigFloatT& operator*=(const BigFloatT& b) {
    BigFloatT res;
    multiplication(*this, b, res);
    *this = std::move(res);
    return *this;
  }

  BigFloatT& operator/=(const BigFloatT& b) {
    division(*this, b, *this);
    return *this;
  }

  friend inline BigFloatT operator+(const BigFloatT& a, const BigFloatT& b) {
    BigFloatT res;
    addition(a, b, res);
    return res;
  }

  friend inline BigFloatT operator-(const BigFloatT& a, const BigFloatT& b) {
    BigFloatT res;
    substraction(a, b, res);
    return res;
  }

  friend inline BigFloatT operator*(const BigFloatT& a, const BigFloatT& b) {
    BigFloatT res;
    multiplication(a, b, res);
    return res;
  }

  friend inline BigFloatT operator/(const BigFloatT& a, const BigFloatT& b) {
    BigFloatT q;
    division(a, b, q);
    return q;
  }

  bool operator==(const BigFloatT& val) const {
    return this->mantissa == val.mantissa && this->exponent == val.exponent;
  }

  bool operator!=(const BigFloatT& val) const { return !(*this == val); }

  friend bool operator>(const BigFloatT& a, const BigFloatT& b) {
    return a.compareTo(b) > 0;
  }

  friend bool operator<(const BigFloatT& a, const BigFloatT& b) {
    return a.compareTo(b) < 0;
  }

  friend bool operator>=(const BigFloatT& a, const BigFloatT& b) {
    return a.compareTo(b) >= 0;
  }

  friend bool operator<=(const BigFloatT& a, const BigFloatT& b) {
    return a.compareTo(b) <= 0;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void addition(const BigFloatT& a,
                       const BigFloatT& b,
                       BigFloatT& result) {
    (void)a;
    (void)b;
    (void)result;
  }

  // reference to the 'result' argument CAN BE THE SAME with the 'a' or
  // 'b' arguments
  friend void substraction(const BigFloatT& a,
                           const BigFloatT& b,
                           BigFloatT& result) {
    (void)a;
    (void)b;
    (void)result;
  }

  // reference to the 'result' argument SHOULD NOT BE THE SAME with the 'a'
  // or 'b' arguments
  friend void multiplication(const BigFloatT& a,
                             const BigFloatT& b,
                             BigFloatT& result) {
    addition(a.exponent, b.exponent, result.exponent);
    multiplication(a.mantissa, b.mantissa, result.mantissa);
  }

  friend void division(BigFloatT dividend,
                       BigFloatT divisor,
                       BigFloatT& quotient) {
    (void)dividend;
    (void)divisor;
    (void)quotient;
  }

  // return -1 if this less than b,
  // return 1 if this bigger than b
  // return 0 if this equal to b
  int compareTo(const BigFloatT& val) const {
    int rv = this->exponent.compareTo(val.exponent);
    if (rv != 0) {
      return rv;
    }

    return this->mantissa.compareTo(val.mantissa);
  }

  friend std::string toPrettyString(const BigFloatT& val,
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

extern template struct BigFloat<32>;
extern template struct BigFloat<64>;
extern template struct BigFloat<128>;
extern template struct BigFloat<256>;
extern template struct BigFloat<512>;
extern template struct BigFloat<1024>;
extern template struct BigFloat<2048>;
extern template struct BigFloat<4096>;

}  // namespace nnoops

#endif
