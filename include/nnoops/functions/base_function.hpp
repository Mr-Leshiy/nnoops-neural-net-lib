#ifndef NNOOPS_LIB_CPP_FUNCTIONS_BASE_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_BASE_FUNCTION_HPP_

#include <array>
#include <string>
#include <type_traits>

#include "nnoops/functions/argument.hpp"
#include "nnoops/functions/point.hpp"

namespace nnoops {

template <typename... Ts>
struct BaseFunction {
  using arg_t = Argument<Ts...>;

  virtual ~BaseFunction() = default;

  virtual double function(const arg_t& argument) const = 0;

  virtual arg_t gradient(const arg_t& argument) const = 0;

  virtual std::string name() const = 0;
};

}  // namespace nnoops

#endif
