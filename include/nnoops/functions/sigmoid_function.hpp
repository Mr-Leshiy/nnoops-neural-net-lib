#ifndef NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_SIGMOID_FUNCTION_HPP_

#include <math.h>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct SigmoidFunction : public BaseFunction<double> {
  using arg_t = typename BaseFunction<double>::arg_t;

  ~SigmoidFunction() override = default;

  double function(const arg_t& argument) const override {
    return 1 / (1 + exp(-get_arg<0>(argument)));
  }

  arg_t gradient(const arg_t& argument) const override {
    double val = exp(-get_arg<0>(argument));
    return val / ((1 + val) * (1 + val));
  }
};

}  // namespace nnoops

#endif