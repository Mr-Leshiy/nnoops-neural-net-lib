#ifndef NNOOPS_LIB_CPP_FUNCTIONS_SUM_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_SUM_FUNCTION_HPP_

#include <stdint.h>

#include <vector>

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

// Represents the sum of the some functions
// for i < M:
//   sum += f_i(x)
template <typename... Args>
struct SumFunction : public BaseFunction<Args...> {
  using arg_t = typename BaseFunction<Args...>::arg_t;

  SumFunction(const std::vector<std::shared_ptr<BaseFunction<Args...>>>& funcs)
      : funcs(funcs) {
    assert(funcs.size() != 0 && "funcs.size() should not equal to zero");
  }
  SumFunction(const std::vector<std::shared_ptr<BaseFunction<Args...>>>& funcs,
              double k)
      : funcs(funcs), k(k) {
    assert(funcs.size() != 0 && "funcs.size() should not equal to zero");
    assert(k != 0 && "k should not equal to zero");
  }
  ~SumFunction() = default;

  double function(const arg_t& argument) const override {
    double sum = 0;
    for (uint64_t i = 0; i < funcs.size(); ++i) {
      sum += funcs[i]->function(argument);
    }
    return sum * k;
  }

  arg_t gradient(const arg_t& argument) const override {
    arg_t res = funcs[0]->gradient(argument);

    for (uint64_t i = 1; i < funcs.size(); ++i) {
      res += funcs[i]->gradient(argument);
    }

    return k * res;
  }

 private:
  // Sum elements
  std::vector<std::shared_ptr<BaseFunction<Args...>>> funcs;
  double k{1.0};
};

}  // namespace nnoops

#endif
