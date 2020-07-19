#include "nnoops/functions/sigmoid_function.hpp"

#include <math.h>

namespace nnoops {

double SigmoidFunction::function(double x) const {
  return 1.0 / (1 + exp(-x));
}

double SigmoidFunction::derivative(double x) const {
  double exp_value = exp(-x);
  return exp_value / ((1 + exp_value) * (1 + exp_value));
}

}  // namespace nnoops