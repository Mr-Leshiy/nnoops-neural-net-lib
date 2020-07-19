#ifndef NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct SigmoidFunction : public BaseFunction {
  SigmoidFunction() = default;
  ~SigmoidFunction() override = default;

  double function(double x) const override;

  double derivative(double x) const override;
};

}  // namespace nnoops

#endif