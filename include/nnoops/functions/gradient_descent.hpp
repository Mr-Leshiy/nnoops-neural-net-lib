#ifndef NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_
#define NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_

#include <cstdint>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

double gradient_descent(const BaseFunction& function,
                        double start_point,
                        double alpha,
                        double eps);

double gradient_descent(const BaseFunction& function,
                        double start_point,
                        double alpha,
                        uint32_t num_iterations);

}  // namespace nnoops

#endif