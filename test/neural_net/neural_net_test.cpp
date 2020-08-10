#include <gtest/gtest.h>

#include "nnoops/functions/linear_function.hpp"
#include "nnoops/functions/linear_function2.hpp"
#include "nnoops/functions/log_loss_function.hpp"
#include "nnoops/functions/sigmoid_function.hpp"
#include "nnoops/neural_net/neural_net.hpp"
#include "nnoops/neural_net/neuron.hpp"

using namespace nnoops;

TEST(Neuron, Basic_test) {
  using neuron_func_types =
      NeuronFuncTypes<1, LinearFunction2<1>, SigmoidFunction>;

  Neuron<neuron_func_types> neuron;

  auto activation_func = neuron.get_activation_function(Point<1>{1.0});

  Argument<Point<1>, double> arg(Point<1>{0.0}, 0.0);
  Argument<Point<1>, double> expected_grad(Point<1>{0.25}, 0.25);
  double expect_val = 0.5;

  Argument<Point<1>, double> grad = activation_func->gradient(arg);
  EXPECT_EQ(grad, expected_grad);

  double val = activation_func->function(arg);
  EXPECT_EQ(val, expect_val);
}

double fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

TEST(NeuralNet, Basic_test) {
  NeuralNet<2, LogLossFunction> neural_net;

  // generate train set
  const static uint64_t M = 10000;
  std::map<Point<2>, double> train_set;
  for (uint64_t i = 0; i < M; ++i) {
    double rand1 = fRand(0, 100);

    Point<2> p = {rand1, rand1};
    train_set[p] = 1.0;

    p = {fRand(0, 100), fRand(0, 100)};
    if (p[0] != p[1]) {
      train_set[p] = 0.0;
    } else {
      train_set[p] = 1.0;
    }
  }

  neural_net.train(train_set, 10000);

  double val = neural_net.calculate(Point<2>{0.1, 15});

  EXPECT_EQ(val, 0);
}
