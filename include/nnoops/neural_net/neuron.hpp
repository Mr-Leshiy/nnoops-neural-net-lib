#ifndef NNOOPS_LIB_CPP_NEURAL_NET_NEURON_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_NEURON_HPP_

#include <stdint.h>

#include <memory>
#include <type_traits>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/point.hpp"
#include "nnoops/neural_net/base_neuron.hpp"

namespace nnoops {

template <uint64_t ArgsSize, typename ZFuncType, typename GFuncType>
struct NeuronFuncTypes {
  using z_func_t = ZFuncType;
  using g_func_t = GFuncType;
  const static uint64_t N = ArgsSize;

  using check_type = typename std::enable_if<
      std::is_base_of<BaseFunction<double>, g_func_t>::value>::type;
};

template <typename NeuronFuncTypes>
struct Neuron : public BaseNeuron {
  using z_func_t = typename NeuronFuncTypes::z_func_t;
  using g_func_t = typename NeuronFuncTypes::g_func_t;
  using z_base_fn_t = typename z_func_t::base_fn_t;
  using g_base_fn_t = typename g_func_t::base_fn_t;

  using z_complementary_fn_t = typename z_func_t::complementary_fn_t;

  const static uint64_t N = NeuronFuncTypes::N;

  Neuron() = default;
  ~Neuron() override = default;

  template <typename... Args>
  std::shared_ptr<z_base_fn_t> get_activation_function(Args... args) const {
    std::shared_ptr<g_base_fn_t> g_fn = std::make_shared<g_func_t>();
    std::shared_ptr<z_base_fn_t> z_fn = std::make_shared<z_func_t>(args...);
    return constructComplexFunction(g_fn, z_fn);
  }

  template <typename... Args>
  std::shared_ptr<z_base_fn_t> get_activation_function(
      std::shared_ptr<g_func_t> g_func, Args... args) const {
    std::shared_ptr<z_base_fn_t> z_fn = std::make_shared<z_func_t>(args...);
    return constructComplexFunction(g_func, z_fn);
  }

  template<typename... Args>
  void update(Args... args) {
    calc_fn = std::make_shared<z_complementary_fn_t>(args...);
  } 

 private:
  std::shared_ptr<typename z_complementary_fn_t::base_fn_t> calc_fn;
};

}  // namespace nnoops

#endif
