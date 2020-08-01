#include <gtest/gtest.h>

#include "nnoops/functions/linear_function2.hpp"
#include "nnoops/functions/sigmoid_function.hpp"
#include "nnoops/neural_net/neural_net.hpp"
#include "nnoops/neural_net/neuron.hpp"

using namespace nnoops;

TEST(Neuron, Basic_test) {
  Neuron<1, LinearFunction2<1>, SigmoidFunction> neuron;

  auto activation_func = neuron.get_activation_function(Point<1>{1.0});

  Argument<Point<1>, double> arg(Point<1>{0.0}, 0.0);

  auto grad = activation_func->gradient(arg);
}

TEST(NeuralNet, Basic_test) {}
