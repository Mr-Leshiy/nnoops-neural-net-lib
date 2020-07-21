#include "nnoops/functions/quadratic_function.hpp"

namespace nnoops {

double QuadraticFunction::function(const Point<1>& x) const {
  return ((a * x * x) + (b * x) + c)[0];
}

double QuadraticFunction::derivative(const Point<1>& x) const {
  return (2 * (a * x) + b)[0];
}

}  // namespace nnoops