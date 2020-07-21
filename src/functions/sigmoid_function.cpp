#include "nnoops/functions/sigmoid_function.hpp"

#include <math.h>

namespace nnoops {

double SigmoidFunction::function(const Point<1>& x) const {
  return 1.0 / (1 + exp(-x[0]));
}

double SigmoidFunction::derivative(const Point<1>& x) const {
  double exp_value = exp(-x[0]);
  return exp_value / ((1 + exp_value) * (1 + exp_value));
}

}  // namespace nnoops