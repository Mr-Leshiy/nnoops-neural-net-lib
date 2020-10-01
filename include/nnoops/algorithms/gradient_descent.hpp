#ifndef NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_
#define NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_

#include <cstdint>
#include <iostream>

#include "nnoops/functions/argument.hpp"
#include "nnoops/functions/base_function.hpp"

namespace nnoops {

namespace {

template <typename... Args>
Argument<Args...> do_gradient_descent(const BaseFunction<Args...>& f,
                                      const Argument<Args...>& x,
                                      double alpha) {
  return x - alpha * f.gradient(x);
}

}  // namespace

template <typename... Args>
Argument<Args...> gradient_descent(const BaseFunction<Args...>& function,
                                   const Argument<Args...>& start_point,
                                   double alpha,
                                   uint64_t num_iterations) {
  Argument<Args...> value = do_gradient_descent(function, start_point, alpha);

  for (uint64_t i = 0; i < num_iterations; ++i) {
    printf("train interation: %d \n", (int)i);
    value = do_gradient_descent(function, value, alpha);
  }

  return value;
}

}  // namespace nnoops

#endif
