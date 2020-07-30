#include <gtest/gtest.h>
#include <math.h>

#include "nnoops/algorithms/gradient_descent.hpp"
#include "nnoops/functions/complex_function.hpp"

using namespace nnoops;

// TEST(GradientDescent, QuadraticFunctionTest) {
//  QuadraticFunction f1(2, 3, 10);
//
//  double alpha = 0.1;
//  double eps = 0.001;
//
//  double res = gradient_descent(f1, 100, alpha, eps);
//
//  double expect = -0.75;
//
//  EXPECT_TRUE(abs(res - expect) < eps * 10);
//
//  QuadraticFunction f2(5, -20, 11);
//
//  alpha = 0.1;
//  eps = 0.001;
//
//  res = gradient_descent(f2, 100, alpha, eps);
//
//  expect = 2;
//
//  EXPECT_TRUE(fabs(res - expect) < eps * 10);
//}

// TEST(GradientDescent, ComplexFunction) {
//  QuadraticFunction f1;
//  QuadraticFunction f2;
//
//  ComplexFunction<QuadraticFunction, QuadraticFunction> complex_function(f1,
//                                                                         f2);
//  double alpha = 0.01;
//  double eps = 0.00001;
//
//  double res = gradient_descent(complex_function, 1, alpha, eps);
//
//  double expect = 0;
//
//  EXPECT_EQ(expect, res);
//  EXPECT_TRUE(abs(res - expect) < eps * 10);
//
//  f1 = QuadraticFunction(2, 3, 1);
//  f2 = QuadraticFunction(1, 2, 0);
//
//  complex_function =
//      ComplexFunction<QuadraticFunction, QuadraticFunction>(f1, f2);
//
//  res = gradient_descent(f2, 10, alpha, eps);
//
//  EXPECT_EQ(expect, res);
//  EXPECT_TRUE(abs(res - expect) < eps * 10);
//}
