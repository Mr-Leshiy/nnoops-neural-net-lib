#ifndef NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_

#include <map>
#include <memory>
#include <type_traits>

#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/point.hpp"
#include "nnoops/functions/sum_function.hpp"
#include "nnoops/neural_net/neuron.hpp"

namespace nnoops {

// N - size of the input data
template <
    uint64_t N,
    typename loss_function_t,
    typename = typename std::enable_if<
        std::is_base_of<BaseFunction<double>, loss_function_t>::value>::type>
struct NeuralNet {
  NeuralNet() = default;

  void train(const std::map<Point<N>, double>& train_set) {
    std::vector<BaseFunction<double>> funcs;

    for (const auto& el : train_set) {
      std::shared_ptr<BaseFunction<double>> loss_fn =
          std::make_shared<loss_function_t>(el.second);
    }
  }

 private:
};

}  // namespace nnoops

#endif
