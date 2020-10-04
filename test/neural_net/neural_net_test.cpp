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

TEST(NeuralNet, Basic_test_1) {
  NeuralNet<2, LogLossFunction> neural_net;

  // generate train set
  const static uint64_t M = 100000;
  std::map<Point<2>, double> train_set;

  // first order curve
  auto curve = [](const Point<2>& point) -> double {
    double a = 2;
    double b = -3;
    double c = 1;
    return a * point[0] + b * point[1] + c;
  };

  auto is_above_curve = [&curve](const Point<2>& point) -> bool {
    if (curve(point) > 0) {
      return true;
    } else {
      return false;
    }
  };

  for (uint64_t i = 0; i < M; ++i) {
    Point<2> p = {fRand(0, 20), fRand(0, 20)};
    train_set[p] = is_above_curve(p);
  }

  neural_net.train(train_set, 10000);

  uint32_t correct_predictions = 0;
  for (const auto& el : train_set) {
    double val = neural_net.calculate(el.first);
    if (val < 0.5 && el.second == 0) {
      ++correct_predictions;
    }
    if (val >= 0.5 && el.second == 1) {
      ++correct_predictions;
    }
  }

  double percentage = (double)correct_predictions / train_set.size();
  printf("percentage: %f \n", percentage);
  EXPECT_GT(percentage, 0.98);

  correct_predictions = 0;
  for (uint64_t i = 0; i < M; ++i) {
    Point<2> p = {fRand(0, 20), fRand(0, 20)};
    double val = neural_net.calculate(p);

    if (val < 0.5 && is_above_curve(p) == 0) {
      ++correct_predictions;
    }

    if (val >= 0.5 && is_above_curve(p) == 1) {
      ++correct_predictions;
    }
  }

  percentage = (double)correct_predictions / M;
  printf("percentage: %f \n", percentage);
  EXPECT_GT(percentage, 0.98);
}

TEST(NeuralNet, Basic_test_2) {
  NeuralNet<2, LogLossFunction> neural_net;

  // generate train set
  const static uint64_t M = 100000;
  std::map<Point<2>, double> train_set;

  // second order curve
  auto curve = [](const Point<2>& point) -> double {
    double a = 2;
    double b = -3;
    double c = 1;
    double d = 4;
    double f = -3;
    double g = -2;

    double x = point[0];
    double y = point[1];
    return (a * x * x) + (b * y * y) + (2 * c * x * y) + (2 * d * x) +
           (2 * f * y) + g;
  };

  auto is_above_curve = [&curve](const Point<2>& point) -> bool {
    if (curve(point) > 0) {
      return true;
    } else {
      return false;
    }
  };

  for (uint64_t i = 0; i < M; ++i) {
    Point<2> p = {fRand(0, 20), fRand(0, 20)};
    train_set[p] = is_above_curve(p);
  }

  neural_net.train(train_set, 10000);

  uint32_t correct_predictions = 0;
  for (const auto& el : train_set) {
    double val = neural_net.calculate(el.first);
    if (val < 0.5 && el.second == 0) {
      ++correct_predictions;
    }
    if (val >= 0.5 && el.second == 1) {
      ++correct_predictions;
    }
  }

  double percentage = (double)correct_predictions / train_set.size();
  printf("percentage: %f \n", percentage);
  EXPECT_GT(percentage, 0.98);

  correct_predictions = 0;
  for (uint64_t i = 0; i < M; ++i) {
    Point<2> p = {fRand(0, 20), fRand(0, 20)};
    double val = neural_net.calculate(p);

    if (val < 0.5 && is_above_curve(p) == 0) {
      ++correct_predictions;
    }

    if (val >= 0.5 && is_above_curve(p) == 1) {
      ++correct_predictions;
    }
  }

  percentage = (double)correct_predictions / M;
  printf("percentage: %f \n", percentage);
  EXPECT_GT(percentage, 0.98);
}
