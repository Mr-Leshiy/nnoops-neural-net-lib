#ifndef NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_

#include <map>
#include <memory>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"
#include "nnoops/neural_net/neuron.hpp"

namespace nnoops {

// N - size of the input data
template <uint64_t N>
struct NeuralNet {
  NeuralNet() = default;
  NeuralNet(std::shared_ptr<BaseFunction<Point<N>, double>> loss_function)
      : loss_function(loss_function) {}

  void train(const std::map<Point<N>, double>& train_set) {
    std::shared_ptr<BaseFunction<Point<N>, double>> activation_function =
        neuron->get_activation_function();

    for (const auto& el : train_set) {

      

    }
  }

 private:
  std::shared_ptr<Neuron<N>> neuron;
  // Log loss function
  std::shared_ptr<BaseFunction<Point<N>, double>> loss_function;
};

}  // namespace nnoops

#endif
