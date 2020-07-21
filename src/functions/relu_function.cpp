#include "nnoops/functions/relu_function.hpp"

#include <algorithm>

namespace nnoops {

double ReLUFunction::function(const Point<1>& x) const {
  return std::max(0.0, x[0]);
}

double ReLUFunction::derivative(const Point<1>& x) const {
  if (x[0] <= 0) {
    return 0;
  }
  return 1;
}
}  // namespace nnoops