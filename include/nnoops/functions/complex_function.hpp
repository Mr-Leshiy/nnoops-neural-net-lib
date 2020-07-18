#ifndef NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_

#include <type_traits>

#include "base_function.hpp"

namespace nnoops {

// Complex function realisation
// funct_t1 f1
// funct_t2 f2
// f1(f2())
template <typename func_t1,
          typename func_t2,
          typename = typename std::enable_if<
              std::is_base_of<BaseFunction, func_t1>::value &&
              std::is_base_of<BaseFunction, func_t2>::value>::type>
struct ComplexFunction : public BaseFunction {
  ~ComplexFunction() override = default;

  ComplexFunction(const func_t1& f1, const func_t2& f2) : f1(f1), f2(f2) {}

  double function(double x) const override { return f1.function(f2.function(x)); }

  double derivative(double x) const override {
    return f2.derivative(x) * f1.derivative(f2.function(x));
  }

 private:
  func_t1 f1;
  func_t2 f2;
};

}  // namespace nnoops

#endif