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

  BigFloat(std::string str, uint64_t accuracy = 1000) : accuracy(accuracy) {
    // find '.' and remove it
    size_t position = str.find('.');
    // does not find '.'
    if (position != std::string::npos) {
      str.erase(position, 1);
      this->exponent = -(int64_t)(str.size() - position);
    }

    this->mantissa = BigIntegerT(str, NumFormat::DEC);
    normalize();
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
    result.exponent = a.exponent + b.exponent;
    multiplication(a.mantissa, b.mantissa, result.mantissa);
    result.normalize();
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
    if (this->exponent < val.exponent) {
      return -1;
    }
    if (this->exponent > val.exponent) {
      return 1;
    }

    return this->mantissa.compareTo(val.mantissa);
  }

  void setAccuracy(uint64_t accuracy) {
    this->accuracy = accuracy;
    this->normalize();
  }

  uint64_t getAccuracy() const { return this->accuracy; }

  BigFloatT inverse() const {
    THROW_ARITH_ERROR(this->mantissa != BigIntegerT::zero_value(),
                      "division by zero");

    return BigFloatT();
  }

  friend std::string toPrettyString(const BigFloatT& val) {
    return toPrettyString(val.mantissa, NumFormat::DEC) + "*e^(" +
           std::to_string(val.exponent) + ")";
  }

 private:
  void normalize() {
    BigIntegerT q = 0;
    BigIntegerT r = 0;
    division(mantissa, 10, q, &r);

    for (; r == 0 || this->exponent < -1 * (int64_t)this->accuracy;
         division(mantissa, 10, q, &r)) {
      ++this->exponent;
      this->mantissa = q;
    }
  }

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
    this->exponent = exp;
  }

 private:
  int64_t exponent{};
  BigIntegerT mantissa{};
  uint64_t accuracy{1000};
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
