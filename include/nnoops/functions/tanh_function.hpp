#ifndef NNOOPS_LIB_CPP_TANH_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_TANH_FUNCTION_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct TanhFunction : public BaseFunction {
  TanhFunction() = default;
  ~TanhFunction() override = default;

  double function(double x) const override;

  double derivative(double x) const override;
};

}  // namespace nnoops

#endif