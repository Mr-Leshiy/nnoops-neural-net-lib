#ifndef NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_

#include <array>
#include <type_traits>

#include "nnoops/functions/argument.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

// N - size of the argument, K - number of arguments
template <typename... Ts>
struct BaseFunction {
  using arg_t = Argument<Ts...>;

  virtual ~BaseFunction() = default;

  virtual double function(const arg_t& argument) const = 0;

  virtual arg_t gradient(const arg_t& argument) const = 0;
};

}  // namespace nnoops

#endif