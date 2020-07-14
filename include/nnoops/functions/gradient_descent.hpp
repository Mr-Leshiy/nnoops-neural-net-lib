#ifndef NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_
#define NNOOPS_LIB_CPP_GRADIENT_DESCENT_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

double gradient_descent(const BaseFunction& f);

}

#endif