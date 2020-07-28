#include "nnoops/gradient_descent.hpp"

#include <math.h>
#include <stdint.h>

namespace nnoops {
//
//namespace {
//
//double do_gradient_descent(const BaseFunction& f, double x, double alpha) {
//  return x - alpha * f.derivative(x);
//}
//
//}  // namespace
//
//double gradient_descent(const BaseFunction& function,
//                        double start_point,
//                        double alpha,
//                        double eps) {
//  double value = do_gradient_descent(function, start_point, alpha);
//  double prev_value;
//
//  do {
//    prev_value = value;
//    value = do_gradient_descent(function, prev_value, alpha);
//  } while (fabs(prev_value - value) > eps);
//
//  return value;
//}
//
//double gradient_descent(const BaseFunction& function,
//                        double start_point,
//                        double alpha,
//                        uint32_t num_iterations) {
//  double value = do_gradient_descent(function, start_point, alpha);
//
//  for (uint32_t i = 0; i < num_iterations; ++i) {
//    value = do_gradient_descent(function, value, alpha);
//  }
//
//  return value;
//}

}  // namespace nnoops