#ifndef NNOOPS_LIB_CPP_LINEAR_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_LINEAR_FUNCTION_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

template <uint32_t N>
struct LinearFunction : public BaseFunction<Point<N>> {
  LinearFunction(Point<N> a, double b) : a(a), b(b) {}

  ~LinearFunction() override = default;

  double function(Argument<Point<N>> argument) const override {
    return a * argument.arg + b;
  }

  Argument<Point<N>> gradient(Argument<Point<N>>) const override {
    return Argument<Point<N>>(a);
  }

 private:
  Point<N> a;
  double b;
};

}  // namespace nnoops

#endif