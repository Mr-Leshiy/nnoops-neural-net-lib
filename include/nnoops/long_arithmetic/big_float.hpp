#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_BIG_DECIMAL_HPP_

#include <math.h>
#include <stdint.h>

#include <string>

#include "nnoops/long_arithmetic/signed_big_integer.hpp"
#include "nnoops/long_arithmetic/unsigned_big_integer.hpp"

namespace nnoops {

// Representation on the big decimal with the arbitrary size
// SIZE should be multiple of 8 (1 byte)
// actual size of the BigDecimal equals to SIZE / 2
// representation is equal to quotient of a / b
template <uint64_t SIZE = 64, typename BASE_T = uint32_t>
struct BigFloat {
  using BigFloatT = BigFloat<SIZE, BASE_T>;
  using BigIntegerT = BigInteger<SIZE, BASE_T>;
  using UBigIntegerT = UBigInteger<SIZE, BASE_T>;

  ~BigFloat() = default;

  BigFloat() = default;

  BigFloat(const BigFloatT& val)
      : exponent(val.exponent),
        mantissa(val.mantissa),
        accuracy(val.accuracy) {}

  BigFloat(BigFloatT&& val)
      : exponent(std::move(val.exponent)),
        mantissa(std::move(val.mantissa)),
        accuracy(std::move(val.accuracy)) {}

  BigFloatT& operator=(const BigFloatT& val) {
    this->exponent = val.exponent;
    this->mantissa = val.mantissa;
    this->accuracy = val.accuracy;
    return *this;
  }

  BigFloatT& operator=(BigFloatT&& val) {
    this->exponent = std::move(val.exponent);
    this->mantissa = std::move(val.mantissa);
    this->accuracy = std::move(val.accuracy);
    return *this;
  }

  BigFloat(std::string str, uint64_t accuracy = 200) : accuracy(accuracy) {
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

  void setAccuracy(int64_t val) {
    this->accuracy = abs(val);
    this->normalize();
  }

  int64_t getAccuracy() const { return (uint64_t)this->accuracy; }

  BigFloatT inverse() const {
    THROW_ARITH_ERROR(this->mantissa != BigIntegerT::zero_value(),
                      "division by zero");

    BigFloatT res(0);
    res.exponent = -this->exponent;
    res.accuracy = this->accuracy;

    BigIntegerT x(10);

    for (int64_t i = 0; i < this->exponent; ++i) {
      x *= 10;
    }

    while (x < this->mantissa) {
      x *= 10;
      --res.exponent;
    }

    BigIntegerT r(1);
    BigIntegerT q;
    while (res.exponent > -1 * this->accuracy &&
           r != BigIntegerT::zero_value()) {
      division(x, this->mantissa, q, &r);
      x = 10 * r;
      res.mantissa *= 10;
      res.mantissa += q;
      --res.exponent;
    }

    res.mantissa.setSign(this->mantissa.getSign());

    return res;
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

    // remove zeros
    for (; r == 0; division(mantissa, 10, q, &r)) {
      ++exponent;
      mantissa = q;
    }

    // normalizing number by its accuracy
    for (; exponent < -1 * accuracy; division(mantissa, 10, q, &r)) {
      ++exponent;
      mantissa = q;
    }

    if (mantissa == 0) {
      exponent = 0;
    }
  }

  template <
      typename T,
      typename = typename std::enable_if<std::is_integral<T>::value>::type>
  void init(T val) {
    if (val == 0) {
      return;
    }

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
  // default accuracy is 200
  int64_t accuracy{200};
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
