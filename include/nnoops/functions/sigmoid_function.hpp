#ifndef NNOOPS_LIB_CPP_FUNCTIONS_SIGMOID_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_SIGMOID_FUNCTION_HPP_

#include <math.h>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct SigmoidFunction : public BaseFunction<double> {
  using base_fn_t = BaseFunction<double>;
  using arg_t = typename BaseFunction<double>::arg_t;

  ~SigmoidFunction() override = default;

  double function(const arg_t& argument) const override {
    return 1.0 / (1.0 + exp(-get_arg<0>(argument)));
  }

  arg_t gradient(const arg_t& argument) const override {
    // use 0.99999999999999999 instead of the 1.0 because of the double
    double val = exp(-get_arg<0>(argument));
    return val / ((1.0 + val) * (1.0 + val));
  }

  std::string name() const override { return "sigmoid_function"; }
};

}  // namespace nnoops

#endif
