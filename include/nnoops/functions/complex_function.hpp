#ifndef NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_COMPLEX_FUNCTION_HPP_

#include <memory>
#include <type_traits>

#include "base_function.hpp"

namespace nnoops {

// Complex function realisation
// funct_t1 f1
// funct_t2 f2
// f1(f2())
template <typename... Ts>
struct ComplexFunction : public BaseFunction<Ts...> {
  using arg_t = typename BaseFunction<Ts...>::arg_t;

  ~ComplexFunction() override = default;

  ComplexFunction(std::shared_ptr<BaseFunction<double>> f1,
                  std::shared_ptr<BaseFunction<Ts...>> f2)
      : f1(f1), f2(f2) {}

  double function(const arg_t& argument) const override {
    return f1->function(f2->function(argument));
  }

  arg_t gradient(const arg_t& argument) const override {
    return f2->gradient(argument) * f1->gradient(f2->function(argument));
  }

 private:
  std::shared_ptr<BaseFunction<double>> f1;
  std::shared_ptr<BaseFunction<Ts...>> f2;
};

}  // namespace nnoops

#endif
