#include "nnoops/functions/tanh_function.hpp"

#include <math.h>

namespace nnoops {

double TanhFunction::function(double x) const {
  double exp1 = exp(x);
  double exp2 = exp(-x);
  return (exp1 - exp2) / (exp1 + exp2);
}

double TanhFunction::derivative(double x) const {
  double exp_value = exp(2 * x);
  return 4 * exp_value / ((exp_value + 1) * (exp_value + 1));
}

}  // namespace nnoops