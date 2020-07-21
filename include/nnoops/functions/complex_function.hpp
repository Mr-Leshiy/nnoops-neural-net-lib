#ifndef NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_

#include <type_traits>

#include "base_function.hpp"

namespace nnoops {

// Complex function realisation
// funct_t1 f1
// funct_t2 f2
// f1(f2())
template <uint32_t N>
struct ComplexFunction : public BaseFunction<N> {
  ~ComplexFunction() override = default;

  ComplexFunction(const BaseFunction<1>& f1, const BaseFunction<N>& f2)
      : f1(f1), f2(f2) {}

  double function(const Point<N>& x) const override {
    return f1.function(Point<1>{f2.function(x)});
  }

  double derivative(const Point<N>& x) const override {
    return f2.derivative(x) * f1.derivative(Point<1>{f2.function(x)});
  }

 private:
  const BaseFunction<1>& f1;
  const BaseFunction<N>& f2;
};

}  // namespace nnoops

#endif