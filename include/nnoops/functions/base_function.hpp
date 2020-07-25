#ifndef NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_

#include <array>
#include <type_traits>

#include "nnoops/functions/point.hpp"
#include "nnoops/functions/argument.hpp"

namespace nnoops {

// N - size of the argument, K - number of arguments
template <typename... Ts>
struct BaseFunction {
  virtual ~BaseFunction() = default;

  virtual double function(Argument<Ts...> argument) const = 0;

  virtual Argument<Ts...> gradient(Argument<Ts...> argument) const = 0;
};

}  // namespace nnoops

#endif