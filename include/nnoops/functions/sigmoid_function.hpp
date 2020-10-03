#ifndef NNOOPS_LIB_CPP_FUNCTIONS_SIGMOID_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_SIGMOID_FUNCTION_HPP_

#include <limits.h>
#include <math.h>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct SigmoidFunction : public BaseFunction<double> {
  using base_fn_t = BaseFunction<double>;
  using arg_t = typename BaseFunction<double>::arg_t;

  ~SigmoidFunction() override = default;

  double function(const arg_t& argument) const override {
    double e = exp(-get_arg<0>(argument));
    return 1.0 / (1.0 + e);
  }

  arg_t gradient(const arg_t& argument) const override {
    double e = exp(-get_arg<0>(argument));
    return e / ((1.0 + e) * (1.0 + e));
  }

  std::string name() const override { return "sigmoid_function"; }
};

}  // namespace nnoops

#endif
