#ifndef NNOOPS_LIB_CPP_QUADRATIC_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_QUADRATIC_FUNCTION_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct QuadraticFunction : public BaseFunction {
  QuadraticFunction() = default;
  QuadraticFunction(double a, double b, double c) : a(a), b(b), c(c) {}

  ~QuadraticFunction() override = default;

  double function(double x) const override;

  double derivative(double x) const override;

 private:
  double a{1.0};
  double b{0};
  double c{0};
};

}  // namespace nnoops

#endif