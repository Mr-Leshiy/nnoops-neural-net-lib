#ifndef NNOOPS_LIB_CPP_NEURAL_NET_NEURON_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_NEURON_HPP_

#include <stdint.h>

#include <memory>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/linear_function2.hpp"
#include "nnoops/functions/point.hpp"
#include "nnoops/neural_net/base_neuron.hpp"

namespace nnoops {

// N - size of the argument
template <uint64_t N>
struct Neuron : public BaseNeuron {
  Neuron(std::shared_ptr<BaseFunction<Point<N>, double>> z_func,
         std::shared_ptr<BaseFunction<double>> g_func)
      : z_func(z_func), g_func(g_func) {}

  ~Neuron() override = default;

  std::shared_ptr<BaseFunction<Point<N>, double>> get_activation_function()
      const {
    return std::make_shared<ComplexFunction<Point<N>, double>>(g_func, z_func);
  }

 private:
  // Linear function
  std::shared_ptr<BaseFunction<Point<N>, double>> z_func;
  // Sigmoid function
  std::shared_ptr<BaseFunction<double>> g_func;
};

}  // namespace nnoops

#endif