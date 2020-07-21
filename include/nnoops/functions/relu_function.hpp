#ifndef NNOOPS_LIB_CPP_RELU_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_RELU_FUNCTION_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct ReLUFunction : public BaseFunction<1> {
  ReLUFunction() = default;
  ~ReLUFunction() override = default;

  double function(const Point<1>& x) const override;

  double derivative(const Point<1>& x) const override;
};

}  // namespace nnoops

#endif
