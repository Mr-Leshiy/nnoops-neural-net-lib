#ifndef NNOOPS_LIB_CPP_LINEAR_FUNCTION2_HPP_
#define NNOOPS_LIB_CPP_LINEAR_FUNCTION2_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

template <uint32_t N>
struct LinearFunction2 : BaseFunction<Point<N>, double> {
  LinearFunction2() = default;

  LinearFunction2(Point<N> x) : x(x) {}

  ~LinearFunction2() override = default;

  double function(Argument<Point<N>, double> argument) const override {}

  Argument<Point<N>, double> gradient(
      Argument<Point<N>, double> argument) const override {}

 private:
  Point<N> x{};
};

}  // namespace nnoops

#endif