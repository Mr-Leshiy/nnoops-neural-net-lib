#include "nnoops/quadratic_function.hpp"

namespace nnoops {

double QuadraticFunction::function(double x) {
  return (a * x * x) + (b * x) + c;
}

double QuadraticFunction::derivative(double x) { return 2 * (a * x) + b; }

}  // namespace nnoops