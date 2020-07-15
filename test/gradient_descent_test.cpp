#include "nnoops/functions/gradient_descent.hpp"

#include <gtest/gtest.h>

#include "nnoops/functions/quadratic_function.hpp"

using namespace nnoops;

TEST(GradientDescent, QuadraticFunctionTest) {
  QuadraticFunction f1(2, 3, 10);

  double alpha = 0.1;
  double eps = 0.001;

  double res = gradient_descent(f1, 100, alpha, eps);

  double expect = -0.75;

  EXPECT_TRUE(abs(res - expect) < eps * 10);

  QuadraticFunction f2(-5, 20, 11);

  alpha = 0.00001;
  eps = 0.001;

  res = gradient_descent(f2, 100, alpha, eps);

  expect = 2;

  EXPECT_EQ(res, expect);
  EXPECT_TRUE(abs(res - expect) < eps * 10);
}
