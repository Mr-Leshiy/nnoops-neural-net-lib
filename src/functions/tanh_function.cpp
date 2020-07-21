#include "nnoops/functions/tanh_function.hpp"

#include <math.h>

namespace nnoops {

double TanhFunction::function(const Point<1>& x) const {
  double exp1 = exp(x[0]);
  double exp2 = exp(-x[0]);
  return (exp1 - exp2) / (exp1 + exp2);
}

double TanhFunction::derivative(const Point<1>& x) const {
  double exp_value = exp(2 * x[0]);
  return 4 * exp_value / ((exp_value + 1) * (exp_value + 1));
}

}  // namespace nnoops