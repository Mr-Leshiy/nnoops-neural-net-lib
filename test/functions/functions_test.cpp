#include <gtest/gtest.h>
#include <math.h>

#include <vector>

#include "nnoops/functions/linear_function.hpp"

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
