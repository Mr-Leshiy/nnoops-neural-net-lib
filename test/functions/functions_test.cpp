#include <gtest/gtest.h>
#include <math.h>

#include <vector>

#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/linear_function.hpp"
#include "nnoops/functions/quadratic_function.hpp"
#include "nnoops/functions/relu_function.hpp"
#include "nnoops/functions/sigmoid_function.hpp"
#include "nnoops/functions/tanh_function.hpp"

using namespace nnoops;

struct FunctionValueTestCase {
  double expected_function_value;
  double expected_derivative_value;
  Point<1> argument;
  std::shared_ptr<BaseFunction<1>> f;
};

struct FunctionValueTest
    : public testing::TestWithParam<FunctionValueTestCase> {};

static std::vector<FunctionValueTestCase> f_value_test_cases = {
    // Quadratic function test cases
    {
        0,
        0,
        Point<1>{0},
        std::make_shared<QuadraticFunction>(),
    },
    {
        0.00001,
        2,
        Point<1>{0},
        std::make_shared<QuadraticFunction>(1, 2, 0.00001),
    },
    {
        37.00002,
        15,
        Point<1>{3},
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },
    {
        19.00002,
        -9,
        Point<1>{-3},
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },

    // ComplexFunction test cases
    {
        16,
        32,
        Point<1>{2},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(),
                                             QuadraticFunction()),
    },
    {
        81,
        108,
        Point<1>{3},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(),
                                             QuadraticFunction()),
    },
    {
        256,
        256,
        Point<1>{4},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(),
                                             QuadraticFunction()),
    },
    {
        153,
        210,
        Point<1>{2},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(2, 3, 1),
                                             QuadraticFunction(1, 2, 0)),
    },
    {
        496,
        504,
        Point<1>{3},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(2, 3, 1),
                                             QuadraticFunction(1, 2, 0)),
    },
    {
        1225,
        990,
        Point<1>{4},
        std::make_shared<ComplexFunction<1>>(QuadraticFunction(2, 3, 1),
                                             QuadraticFunction(1, 2, 0)),
    },

    // SigmoidFunction test cases
    {
        0.5,
        0.25,
        Point<1>{0},
        std::make_shared<SigmoidFunction>(),
    },
    {
        (1.0 / (1 + exp(-1))),
        (exp(-1) / ((1 + exp(-1)) * (1 + exp(-1)))),
        Point<1>{1},
        std::make_shared<SigmoidFunction>(),
    },
    {
        (1.0 / (1 + exp(1))),
        (exp(1) / ((1 + exp(1)) * (1 + exp(1)))),
        Point<1>{-1},
        std::make_shared<SigmoidFunction>(),
    },

    // LinearFunction test cases
    {
        -7.236,
        1,
        Point<1>{-7.236},
        std::make_shared<LinearFunction>(),
    },
    {
        23,
        2,
        Point<1>{10},
        std::make_shared<LinearFunction>(2, 3),
    },
    {
        -17,
        -2,
        Point<1>{2},
        std::make_shared<LinearFunction>(-2, -13),
    },

    // ReLUFunction test cases
    {
        123.123,
        1,
        Point<1>{123.123},
        std::make_shared<ReLUFunction>(),
    },
    {
        0,
        0,
        Point<1>{-123.123},
        std::make_shared<ReLUFunction>(),
    },
    {
        0,
        0,
        Point<1>{0},
        std::make_shared<ReLUFunction>(),
    },

    // TanhFunction test cases
    {
        0,
        1,
        Point<1>{0},
        std::make_shared<TanhFunction>(),
    },
    {
        (exp(1) - exp(-1)) / (exp(1) + exp(-1)),
        4 * exp(2) / ((exp(2) + 1) * (exp(2) + 1)),
        Point<1>{1},
        std::make_shared<TanhFunction>(),
    },
    {
        (exp(-1) - exp(1)) / (exp(1) + exp(-1)),
        4 * exp(-2) / ((exp(-2) + 1) * (exp(-2) + 1)),
        Point<1>{-1},
        std::make_shared<TanhFunction>(),
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
