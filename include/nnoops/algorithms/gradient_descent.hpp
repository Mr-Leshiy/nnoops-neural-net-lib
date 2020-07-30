#ifndef NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_
#define NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_

#include <cstdint>

#include "nnoops/functions/argument.hpp"
#include "nnoops/functions/base_function.hpp"

namespace nnoops {

namespace {

template<typename... Args>
double do_gradient_descent(const BaseFunction<Args...>& f,
                           const Argument<Args...>& x,
                           double alpha) {
  return x - alpha * f.derivative(x);
}

}  // namespace

template <typename... Args>
double gradient_descent(const BaseFunction<Args...>& function,
                        const Argument<Args...>& start_point,
                        double alpha,
                        double eps);

template <typename... Args>
double gradient_descent(const BaseFunction<Args...>& function,
                        const Argument<Args...>& start_point,
                        double alpha,
                        uint32_t num_iterations);

}  // namespace nnoops

#endif