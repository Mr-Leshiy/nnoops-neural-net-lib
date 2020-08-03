#ifndef NNOOPS_LIB_CPP_FUNCTIONS_LINEAR_FUNCTION2_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_LINEAR_FUNCTION2_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

template <uint64_t N>
struct LinearFunction;

template <uint64_t N>
struct LinearFunction2 : public BaseFunction<Point<N>, double> {
  using base_fn_t = BaseFunction<Point<N>, double>;
  using arg_t = typename BaseFunction<Point<N>, double>::arg_t;
  using complementary_fn_t = LinearFunction<N>;

  LinearFunction2(Point<N> x) : x(x) {}

  ~LinearFunction2() override = default;

  double function(const arg_t& argument) const override {
    return x * get_arg<0>(argument) + get_arg<1>(argument);
  }

  arg_t gradient(const arg_t&) const override { return arg_t(x, 1.0); }

 private:
  Point<N> x{};
};

}  // namespace nnoops

#endif