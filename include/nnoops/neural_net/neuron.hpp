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

// ArgSize - size of the argument
template <uint64_t ArgSize, typename ZFuncType, typename GFuncType>
struct NeuronFuncTypes {
  const static uint64_t N = ArgSize;
  using z_func_t = ZFuncType;
  using g_func_t = GFuncType;

  using check_type = typename std::enable_if<
      std::is_base_of<BaseFunction<Point<N>, double>, z_func_t>::value &&
      std::is_base_of<BaseFunction<double>, g_func_t>::value>::type;
};

template <typename NeuronFuncTypes>
struct Neuron : public BaseNeuron {
  using z_func_t = typename NeuronFuncTypes::z_func_t;
  using g_func_t = typename NeuronFuncTypes::g_func_t;
  const static uint64_t N = NeuronFuncTypes::N;

  Neuron() = default;
  ~Neuron() override = default;

  std::shared_ptr<BaseFunction<Point<N>, double>> get_activation_function(
      const Point<N>& val) const {
    return std::make_shared<ComplexFunction<Point<N>, double>>(
        std::make_shared<g_func_t>(), std::make_shared<z_func_t>(val));
  }

  std::shared_ptr<BaseFunction<Point<N>, double>> get_activation_function(
      const Point<N>& val, std::shared_ptr<g_func_t> g_func) const {
    return std::make_shared<ComplexFunction<Point<N>, double>>(
        g_func, std::make_shared<z_func_t>(val));
  }
};

}  // namespace nnoops

#endif
