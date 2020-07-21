#ifndef NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_

#include <cassert>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct SigmoidFunction : public BaseFunction<1> {
  SigmoidFunction() = default;
  ~SigmoidFunction() override = default;

  double function(const Point<1>& x) const override;

  double derivative(const Point<1>& x) const override;
};

}  // namespace nnoops

#endif