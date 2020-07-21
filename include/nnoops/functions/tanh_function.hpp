#ifndef NNOOPS_LIB_CPP_TANH_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_TANH_FUNCTION_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct TanhFunction : public BaseFunction<1> {
  TanhFunction() = default;
  ~TanhFunction() override = default;

  double function(const Point<1>& x) const override;

  double derivative(const Point<1>& x) const override;
};

}  // namespace nnoops

#endif