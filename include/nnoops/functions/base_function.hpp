#ifndef NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_

#include <type_traits>

#include "nnoops/functions/point.hpp"

namespace nnoops {

template <uint32_t N>
struct BaseFunction {
  virtual ~BaseFunction() = default;

  virtual double function(const Point<N>& x) const = 0;

  virtual double derivative(const Point<N>& x) const = 0;
};

}  // namespace nnoops

#endif