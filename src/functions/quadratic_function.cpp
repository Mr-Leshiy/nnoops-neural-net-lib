#include "nnoops/functions/quadratic_function.hpp"

namespace nnoops {

double QuadraticFunction::function(double x) const {
  return (a * x * x) + (b * x) + c;
}

double QuadraticFunction::derivative(double x) const { return 2 * (a * x) + b; }

}  // namespace nnoops