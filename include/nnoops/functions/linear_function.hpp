#ifndef NNOOPS_LIB_CPP_LINEAR_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_LINEAR_FUNCTION_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {
struct LinearFunction : BaseFunction {
  LinearFunction() = default;
  LinearFunction(double a, double b) : a(a), b(b) {
    assert(a != 0 && "'a' field should not equal to zero");
  }
  ~LinearFunction() override = default;

  double function(double x) const override;

  double derivative(double x) const override;

 private:
  double a{1.0};
  double b{0};
};

}  // namespace nnoops

#endif