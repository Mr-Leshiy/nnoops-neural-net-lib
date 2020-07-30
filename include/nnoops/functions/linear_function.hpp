#ifndef NNOOPS_LIB_CPP_FUNCTIONS_LINEAR_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_LINEAR_FUNCTION_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

// N - size of the argument
template <uint64_t N>
struct LinearFunction : public BaseFunction<Point<N>> {
  using arg_t = typename BaseFunction<Point<N>>::arg_t;

  LinearFunction(Point<N> a, double b) : a(a), b(b) {}

  ~LinearFunction() override = default;

  double function(const arg_t& argument) const override {
    return a * get_arg<0>(argument) + b;
  }

  arg_t gradient(const arg_t&) const override { return arg_t(a); }

 private:
  Point<N> a;
  double b;
};

}  // namespace nnoops

#endif