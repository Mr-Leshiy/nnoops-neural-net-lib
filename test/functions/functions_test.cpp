#include <gtest/gtest.h>
#include <math.h>

#include <vector>

#include "nnoops/functions/linear_function.hpp"

using namespace nnoops;

struct FunctionValueTestCase {
  double expected_function_value;
  Argument<Point<1>> expected_derivative_value;
  Argument<Point<1>> argument;
  std::shared_ptr<BaseFunction<Point<1>>> f;
};

struct FunctionValueTest
    : public testing::TestWithParam<FunctionValueTestCase> {};

static std::vector<FunctionValueTestCase> f_value_test_cases = {
    // Linear function test cases
    {
        0,
        Argument<Point<1>>(Point<1>{1.0}),
        Argument<Point<1>>(Point<1>{0}),
        std::make_shared<LinearFunction<1>>(Point<1>{1}, 0),
    },
};

TEST_P(FunctionValueTest, function_test) {
  auto value = GetParam();

  EXPECT_EQ(value.f->function(value.argument), value.expected_function_value);
}

TEST_P(FunctionValueTest, derivative_test) {
  auto value = GetParam();

  EXPECT_EQ(get_arg<0>(value.f->gradient(value.argument)),
            get_arg<0>(value.expected_derivative_value));
}

INSTANTIATE_TEST_SUITE_P(FunctionValue,
                         FunctionValueTest,
                         testing::ValuesIn(f_value_test_cases));
