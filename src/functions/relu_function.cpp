#include "nnoops/functions/relu_function.hpp"

#include <algorithm>

namespace nnoops {

double ReLUFunction::function(double x) const { return std::max(0.0, x); }

double ReLUFunction::derivative(double x) const {
  if (x <= 0) {
    return 0;
  }
  return 1;
}
}  // namespace nnoops