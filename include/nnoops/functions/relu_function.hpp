#ifndef NNOOPS_LIB_CPP_RELU_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_RELU_FUNCTION_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct ReLUFunction : public BaseFunction {
  ReLUFunction() = default;
  ~ReLUFunction() override = default;

  double function(double x) const override;

  double derivative(double x) const override;
};

}  // namespace nnoops

#endif
