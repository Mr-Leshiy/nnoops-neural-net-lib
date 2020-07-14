#include <gtest/gtest.h>

#include <vector>

#include "nnoops/quadratic_function.hpp"

using namespace nnoops;

struct FunctionValueTestCase {
  double expected_function_value;
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
        std::make_shared<QuadraticFunction>(),
    },
    {
        0.00001,
        0,
        std::make_shared<QuadraticFunction>(1, 2, 0.00001),
    },
    {
        37.00002,
        3,
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },
    {
        19.00002,
        -3,
        std::make_shared<QuadraticFunction>(2, 3, 10.00002),
    },

};

TEST_P(FunctionValueTest, Basic) {
  auto value = GetParam();

  EXPECT_EQ(value.f->function(value.argument), value.expected_function_value);
}

INSTANTIATE_TEST_SUITE_P(FunctionValue,
                         FunctionValueTest,
                         testing::ValuesIn(f_value_test_cases));