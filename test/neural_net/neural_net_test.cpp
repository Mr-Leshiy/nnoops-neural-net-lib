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
  Argument<Point<1>, double> expected_grad(Point<1>{0.25}, 0.25);
  double expect_val = 0.5;

  Argument<Point<1>, double> grad = activation_func->gradient(arg);
  EXPECT_EQ(grad, expected_grad);

  double val = activation_func->function(arg);
  EXPECT_EQ(val, expect_val);
}

TEST(NeuralNet, Basic_test) {}
