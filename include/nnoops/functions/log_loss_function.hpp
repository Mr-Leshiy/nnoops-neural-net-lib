#ifndef NNOOPS_LIB_CPP_FUNCTIONS_LOG_LOSS_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_LOG_LOSS_FUNCTION_HPP_

#include <math.h>
#include <stdint.h>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

struct LogLossFunction : public BaseFunction<double> {
  using base_fn_t = BaseFunction<double>;
  using arg_t = typename BaseFunction<double>::arg_t;

  LogLossFunction() = default;

  LogLossFunction(const Argument<double>& coef) : y(get_arg<0>(coef)) {
    assert((y == 0 || y == 1) && " y should be equal to 0.0 or to 1.0");
  }
  LogLossFunction(double y) : y(y) {
    assert((y == 0 || y == 1) && " y should be equal to 0.0 or to 1.0");
  }

  ~LogLossFunction() override = default;

  double function(const arg_t& argument) const override {
    const double& val = get_arg<0>(argument);
    assert((val < 1.0 && val > 0.0) &&
           "argument value should be in the interval of (0, 1)");
    return -(y * log(val) + (1 - y) * log(1 - val));
  }

  arg_t gradient(const arg_t& argument) const override {
    const double& val = get_arg<0>(argument);
    assert((val < 1.0 && val > 0.0) &&
           "argument value should be in the interval of (0, 1)");
    return -(y - val) / (val * (1 - val));
  }

 private:
  double y{0.0};
};

}  // namespace nnoops

#endif