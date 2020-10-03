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

  printf("Start gradient descent \n");
  printf("[");
  for (uint64_t i = 0; i < num_iterations; ++i) {
    double progress = (double)i / num_iterations * 100;
    if (progress - floor(progress) == 0) {
      printf("*");
      fflush(stdout);
    }

    value = do_gradient_descent(function, value, alpha);
  }
  printf("]\n");

  return value;
}

}  // namespace nnoops

#endif
