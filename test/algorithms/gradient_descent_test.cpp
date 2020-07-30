#include <gtest/gtest.h>
#include <math.h>

#include "nnoops/algorithms/gradient_descent.hpp"
#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/log_loss_function.hpp"

using namespace nnoops;

TEST(GradientDescent, LogLossFunction_test) {
  LogLossFunction f1;

  LogLossFunction::arg_t start_point{0.99};

  auto res = gradient_descent(f1, start_point, 0.001, 100);

  EXPECT_GT(get_arg<0>(start_point), get_arg<0>(res));
}
