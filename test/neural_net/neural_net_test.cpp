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
  const static uint64_t M = 100000;
  std::map<Point<2>, double> train_set;

  // equation of a line
  auto line = [](const Point<2>& point) -> double {
    double a = 2;
    double b = -3;
    double c = 1;
    return a * point[0] + b * point[1] + c;
  };

  for (uint64_t i = 0; i < M; ++i) {
    Point<2> p = {fRand(0, 20), fRand(0, 20)};

    if (line(p) <= 0) {
      train_set[p] = 0.0;
    } else {
      train_set[p] = 1.0;
    }
  }

  neural_net.train(train_set, 10000);

  double val = neural_net.calculate(Point<2>{0.1, 15});
  EXPECT_EQ(val, 0);

  val = neural_net.calculate(Point<2>{0.2, 0.2});

  EXPECT_EQ(val, 1);
}