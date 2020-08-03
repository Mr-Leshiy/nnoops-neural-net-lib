#ifndef NNOOPS_LIB_CPP_FUNCTIONS_COMPLEX_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_COMPLEX_FUNCTION_HPP_

#include <memory>
#include <type_traits>

#include "base_function.hpp"

namespace nnoops {

// Complex function realisation
// funct_t1 f1
// funct_t2 f2
// f1(f2())
template <typename... Args>
struct ComplexFunction : public BaseFunction<Args...> {
  using base_fn_t = BaseFunction<Args...>;
  using arg_t = typename BaseFunction<Args...>::arg_t;

  ~ComplexFunction() override = default;

  ComplexFunction(std::shared_ptr<BaseFunction<double>> f1,
                  std::shared_ptr<base_fn_t> f2)
      : f1(f1), f2(f2) {}

  double function(const arg_t& argument) const override {
    return f1->function(f2->function(argument));
  }

  arg_t gradient(const arg_t& argument) const override {
    return f2->gradient(argument) *
           get_arg<0>(f1->gradient(f2->function(argument)));
  }

 private:
  std::shared_ptr<BaseFunction<double>> f1;
  std::shared_ptr<base_fn_t> f2;
};

template <typename... Args>
std::shared_ptr<BaseFunction<Args...>> constructComplexFunction(
    std::shared_ptr<BaseFunction<double>> f1,
    std::shared_ptr<BaseFunction<Args...>> f2) {
  return std::make_shared<ComplexFunction<Args...>>(f1, f2);
}

}  // namespace nnoops

#endif
