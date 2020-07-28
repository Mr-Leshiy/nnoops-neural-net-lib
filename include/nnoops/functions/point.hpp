#ifndef NNOOPS_LIB_FUNCTIONS_CPP_POINT_HPP_
#define NNOOPS_LIB_FUNCTIONS_CPP_POINT_HPP_

#include <stdint.h>

#include <array>
#include <cassert>
#include <stdexcept>
#include <type_traits>

namespace nnoops {

// This struct is only for the compile time type validation
struct CheckPoint {
  virtual ~CheckPoint() = default;
};

template <uint32_t N, typename = typename std::enable_if<N != 0>::type>
struct Point : public CheckPoint {
  Point() = default;

  Point(const Point<N>& point) : x(point.x) {}

  Point(Point<N>&& point) : x(std::move(point.x)) {}

  Point(const std::array<double, N> val) : x(val) {}

  Point(const std::initializer_list<double>& list) {
    if (list.size() != N) {
      throw std::out_of_range("invalid initializer list size");
    }
    uint32_t i = 0;
    for (const auto& el : list) {
      this->x[i++] = el;
    }
  }

  Point<N>& operator=(const Point<N>& point) {
    this->x = point.x;
    return *this;
  }

  Point<N>& operator=(const std::array<double, N> val) {
    this->x = val;
    return *this;
  }

  Point<N>& operator=(const std::initializer_list<double>& list) {
    if (list.size() != N) {
      throw std::out_of_range("invalid initializer list size");
    }
    uint32_t i = 0;
    for (const auto& el : list) {
      this->x[i++] = el;
    }
    return *this;
  }

  Point<N>& operator=(Point<N>&& point) {
    this->x = std::move(point.x);
    return *this;
  }

  double& operator[](uint32_t index) {
    if (index >= N) {
      throw std::out_of_range("index out of range");
    }
    return this->x[index];
  }

  Point<N>& operator+=(double val) {
    for (uint32_t i = 0; i < N; ++i) {
      this->x[i] += val;
    }
    return *this;
  }

  Point<N>& operator+=(const Point<N>& point) {
    for (uint32_t i = 0; i < N; ++i) {
      this->x[i] += point.x[i];
    }
    return *this;
  }

  Point<N>& operator-=(double val) {
    for (uint32_t i = 0; i < N; ++i) {
      this->x[i] -= val;
    }
    return *this;
  }

  Point<N>& operator-=(const Point<N>& point) {
    for (uint32_t i = 0; i < N; ++i) {
      this->x[i] -= point.x[i];
    }
    return *this;
  }

  Point<N>& operator*=(double val) {
    for (uint32_t i = 0; i < N; ++i) {
      this->x[i] *= val;
    }
    return *this;
  }

  Point<N>& operator++() {
    // postfix operator
    for (uint32_t i = 0; i < N; ++i) {
      ++this->x[i];
    }
    return *this;
  }

  Point<N> operator++(int) {
    // prefix operator
    Point<N> ret = *this;
    ++(*this);
    return ret;
  }

  Point<N>& operator--() {
    // postfix operator
    for (uint32_t i = 0; i < N; ++i) {
      --this->x[i];
    }
    return *this;
  }

  Point<N> operator--(int) {
    // prefix operator
    Point<N> ret = *this;
    --(*this);
    return ret;
  }

  friend inline Point<N> operator+(const Point<N>& point1,
                                   const Point<N>& point2) {
    return std::move(Point(point1) += point2);
  }

  friend inline Point<N> operator+(double val, const Point<N>& point) {
    return std::move(Point(point) += val);
  }

  friend inline Point<N> operator+(const Point<N>& point, double val) {
    return std::move(Point(point) += val);
  }

  friend inline Point<N> operator-(const Point<N>& point1,
                                   const Point<N>& point2) {
    return std::move(Point(point1) -= point2);
  }

  friend inline Point<N> operator-(double val, const Point<N>& point) {
    return std::move(Point(point) -= -val);
  }

  friend inline Point<N> operator-(const Point<N>& point, double val) {
    return std::move(Point(point) -= val);
  }

  friend inline double operator*(const Point<N>& point1,
                                 const Point<N>& point2) {
    double sum = 0.0;
    for (uint32_t i = 0; i < N; ++i) {
      sum += point1.x[i] * point2.x[i];
    }
    return sum;
  }

  friend inline Point<N> operator*(double val, const Point<N>& point) {
    return std::move(Point(point) *= val);
  }

  friend inline Point<N> operator*(const Point<N>& point, double val) {
    return std::move(Point(point) *= val);
  }

  friend inline bool operator==(const Point<N>& point1,
                                const Point<N>& point2) {
    return point1.x == point2.x;
  }

  friend inline bool operator!=(const Point<N>& point1,
                                const Point<N>& point2) {
    return point1.x != point2.x;
  }

 private:
  std::array<double, N> x{};
};

}  // namespace nnoops

#endif
