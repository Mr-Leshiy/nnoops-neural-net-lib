#include "nnoops/functions/complex_function.hpp"

#include <gtest/gtest.h>

#include "nnoops/functions/quadratic_function.hpp"

using namespace nnoops;

TEST(ComplexFunction, function_test) {
  QuadraticFunction f1;
  QuadraticFunction f2;

  ComplexFunction<QuadraticFunction, QuadraticFunction> complex_function(f1,
                                                                         f2);
  ASSERT_EQ(complex_function.function(2), 16);
  ASSERT_EQ(complex_function.function(3), 81);
  ASSERT_EQ(complex_function.function(4), 256);

  f1 = QuadraticFunction(2, 3, 1);
  f2 = QuadraticFunction(1, 2, 0);
  complex_function =
      ComplexFunction<QuadraticFunction, QuadraticFunction>(f1, f2);

  ASSERT_EQ(complex_function.function(2), 153);
  ASSERT_EQ(complex_function.function(3), 496);
  ASSERT_EQ(complex_function.function(4), 1225);
}

TEST(ComplexFunction, derivative_test) {
  QuadraticFunction f1;
  QuadraticFunction f2;

  ComplexFunction<QuadraticFunction, QuadraticFunction> complex_function(f1,
                                                                         f2);
  ASSERT_EQ(complex_function.derivative(2), 32);
  ASSERT_EQ(complex_function.derivative(3), 108);
  ASSERT_EQ(complex_function.derivative(4), 256);

  f1 = QuadraticFunction(2, 3, 1);
  f2 = QuadraticFunction(1, 2, 0);
  complex_function =
      ComplexFunction<QuadraticFunction, QuadraticFunction>(f1, f2);

  ASSERT_EQ(complex_function.derivative(2), 210);
  ASSERT_EQ(complex_function.derivative(3), 504);
  ASSERT_EQ(complex_function.derivative(4), 990);
}