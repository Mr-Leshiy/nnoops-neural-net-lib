#include "nnoops/functions/linear_function.hpp"

namespace nnoops {

double LinearFunction::function(double x) const { return a * x + b; }

double LinearFunction::derivative(double) const { return a; }

}  // namespace nnoops