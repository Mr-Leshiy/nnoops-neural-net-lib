#ifndef NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_NEURAL_NET_HPP_

#include <map>
#include <memory>
#include <type_traits>

#include "nnoops/algorithms/gradient_descent.hpp"
#include "nnoops/functions/base_function.hpp"
#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/linear_function2.hpp"
#include "nnoops/functions/point.hpp"
#include "nnoops/functions/sigmoid_function.hpp"
#include "nnoops/functions/sum_function.hpp"
#include "nnoops/neural_net/neuron.hpp"

namespace nnoops {

// N - size of the input data
template <uint64_t N, typename loss_function_t>
struct NeuralNet {
 private:
  using check_type = typename std::enable_if<
      std::is_base_of<BaseFunction<double>, loss_function_t>::value>::type;

 public:
  NeuralNet() = default;

  void train(const std::map<Point<N>, double>& train_set, uint64_t iterations) {
    std::vector<BaseFunction<Point<N>, double>> funcs;
    std::shared_ptr<SigmoidFunction> g_func =
        std::make_shared<SigmoidFunction>();

    for (const auto& el : train_set) {
      std::shared_ptr<BaseFunction<double>> loss_fn =
          std::make_shared<loss_function_t>(el.second);

      std::shared_ptr<BaseFunction<Point<N>, double>> activation_fn =
          neuron.get_activation_function(el.first, g_func);
      funcs.push_back(std::make_shared<ComplexFunction<Point<N>, double>>(
          loss_fn, activation_fn));
    }

    std::shared_ptr<SumFunction<Point<N>, double>> cost_function =
        std::make_shared<SumFunction<Point<N>, double>>(funcs,
                                                        1.0 / funcs.size());

    Argument<Point<N>, double> start_point(
        Point<N>(std::vector<double>(N, 1.0)), 0.0);

    double alpha = 0.0001;
    Argument<Point<N>, double> res_coef =
        gradient_descent(cost_function, start_point, alpha, iterations);
  }

 private:
  using func_types = NeuronFuncTypes<N, LinearFunction2<N>, SigmoidFunction>;
  Neuron<func_types> neuron;
};

}  // namespace nnoops

#endif
