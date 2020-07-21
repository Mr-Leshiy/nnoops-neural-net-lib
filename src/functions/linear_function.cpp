#include "nnoops/functions/linear_function.hpp"

namespace nnoops {

double LinearFunction::function(const Point<1>& x) const {
  return (a * x + b)[0];
}

double LinearFunction::derivative(const Point<1>&) const { return a; }

}  // namespace nnoops