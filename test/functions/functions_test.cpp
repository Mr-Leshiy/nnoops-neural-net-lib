#include <gtest/gtest.h>

#include <vector>

#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/quadratic_function.hpp"

using namespace nnoops;

struct FunctionValueTestCase {
  double expected_function_value;
  double expected_derivative_value;
  double argument;
  std::shared_ptr<BaseFunction> f;
};

struct FunctionValueTest
    : public testing::TestWithParam<FunctionValueTestCase> {};

static std::vector<FunctionValueTestCase> f_value_test_cases = {
    // Quadratic function test cases
    {
        0,
        0,
        0,
        std::make_shared<QuadraticFunction>(),
    },
    {
        0.00001,
        2,
        0,
        std::make_shared<QuadraticFunction>(1, 2, 0.00001),
    },
    {
        37.00002,
        15,
        3,
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },
    {
        19.00002,
        -9,
        -3,
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },

    // ComplexFunction test cases
    {
        16,
        32,
        2,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(), QuadraticFunction()),
    },
    {
        81,
        108,
        3,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(), QuadraticFunction()),
    },
    {
        256,
        256,
        4,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(), QuadraticFunction()),
    },
    {
        153,
        210,
        2,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(2, 3, 1), QuadraticFunction(1, 2, 0)),
    },
    {
        496,
        504,
        3,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(2, 3, 1), QuadraticFunction(1, 2, 0)),
    },
    {
        1225,
        990,
        4,
        std::make_shared<ComplexFunction<QuadraticFunction, QuadraticFunction>>(
            QuadraticFunction(2, 3, 1), QuadraticFunction(1, 2, 0)),
    },
};

TEST_P(FunctionValueTest, function_test) {
  auto value = GetParam();

  EXPECT_EQ(value.f->function(value.argument), value.expected_function_value);
}

TEST_P(FunctionValueTest, derivative_test) {
  auto value = GetParam();

  EXPECT_EQ(value.f->derivative(value.argument),
            value.expected_derivative_value);
}

INSTANTIATE_TEST_SUITE_P(FunctionValue,
                         FunctionValueTest,
                         testing::ValuesIn(f_value_test_cases));
