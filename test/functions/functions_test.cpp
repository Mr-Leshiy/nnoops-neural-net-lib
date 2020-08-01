#include <gtest/gtest.h>
#include <math.h>

#include <vector>

#include "nnoops/functions/complex_function.hpp"
#include "nnoops/functions/linear_function.hpp"
#include "nnoops/functions/linear_function2.hpp"
#include "nnoops/functions/log_loss_function.hpp"
#include "nnoops/functions/sigmoid_function.hpp"
#include "nnoops/functions/sum_function.hpp"

using namespace nnoops;

using arg_t = Argument<Point<1>>;

struct FunctionValueTestCase {
  double expected_function_value;
  arg_t expected_derivative_value;
  arg_t argument;
  std::shared_ptr<BaseFunction<Point<1>>> f;
};

struct FunctionValueTest
    : public testing::TestWithParam<FunctionValueTestCase> {};

static std::vector<FunctionValueTestCase> f_value_test_cases = {
    // Linear function test cases
    {
        0,
        arg_t(Point<1>{1.0}),
        arg_t(Point<1>{0}),
        std::make_shared<LinearFunction<1>>(Point<1>{1}, 0),
    },
    {
        5.678,
        arg_t(Point<1>{1.0}),
        arg_t(Point<1>{5.678}),
        std::make_shared<LinearFunction<1>>(Point<1>{1}, 0),
    },
    {
        15.678,
        arg_t(Point<1>{1.0}),
        arg_t(Point<1>{5.678}),
        std::make_shared<LinearFunction<1>>(Point<1>{1}, 10),
    },
    {
        12.67,
        arg_t(Point<1>{2.67}),
        arg_t(Point<1>{1.0}),
        std::make_shared<LinearFunction<1>>(Point<1>{2.67}, 10),
    },
    // Complex function test cases
    {
        0.5,
        arg_t(Point<1>{0.25}),
        arg_t(Point<1>{0.0}),
        std::make_shared<ComplexFunction<Point<1>>>(
            std::make_shared<SigmoidFunction>(),
            std::make_shared<LinearFunction<1>>(Point<1>{1.0}, 0)),

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

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

using arg2_t = Argument<Point<1>, double>;

struct FunctionValueTestCase2 {
  double expected_function_value;
  arg2_t expected_derivative_value;
  arg2_t argument;
  std::shared_ptr<BaseFunction<Point<1>, double>> f;
};

struct FunctionValueTest2
    : public testing::TestWithParam<FunctionValueTestCase2> {};

static std::vector<FunctionValueTestCase2> f_value_test_cases2 = {
    // Linear function2 test cases
    {
        0,
        arg2_t(Point<1>{1.0}, 1.0),
        arg2_t(Point<1>{0}, 0),
        std::make_shared<LinearFunction2<1>>(Point<1>{1.0}),
    },
    {
        2.56,
        arg2_t(Point<1>{1.0}, 1.0),
        arg2_t(Point<1>{0}, 2.56),
        std::make_shared<LinearFunction2<1>>(Point<1>{1.0}),
    },
    {
        6.0,
        arg2_t(Point<1>{3.44}, 1.0),
        arg2_t(Point<1>{1.0}, 2.56),
        std::make_shared<LinearFunction2<1>>(Point<1>{3.44}),
    },
    // Complex function test cases
    {
        0.5,
        arg2_t(Point<1>{0.25}, 0.25),
        arg2_t(Point<1>{0.0}, 0.0),
        std::make_shared<ComplexFunction<Point<1>, double>>(
            std::make_shared<SigmoidFunction>(),
            std::make_shared<LinearFunction2<1>>(Point<1>{1.0})),

    },
};

TEST_P(FunctionValueTest2, function_test) {
  auto value = GetParam();

  EXPECT_EQ(value.f->function(value.argument), value.expected_function_value);
}

TEST_P(FunctionValueTest2, derivative_test) {
  auto value = GetParam();

  EXPECT_EQ(get_arg<0>(value.f->gradient(value.argument)),
            get_arg<0>(value.expected_derivative_value));

  EXPECT_EQ(get_arg<1>(value.f->gradient(value.argument)),
            get_arg<1>(value.expected_derivative_value));
}

INSTANTIATE_TEST_SUITE_P(FunctionValue,
                         FunctionValueTest2,
                         testing::ValuesIn(f_value_test_cases2));

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

using arg3_t = Argument<double>;

struct FunctionValueTestCase3 {
  double expected_function_value;
  arg3_t expected_derivative_value;
  arg3_t argument;
  std::shared_ptr<BaseFunction<double>> f;
};

struct FunctionValueTest3
    : public testing::TestWithParam<FunctionValueTestCase3> {};

static std::vector<FunctionValueTestCase3> f_value_test_cases3 = {
    // Linear function2 test cases
    {
        0.5,
        arg3_t(0.25),
        arg3_t(0),
        std::make_shared<SigmoidFunction>(),
    },
    // Log Loss function test cases
    {
        -log(0.98),
        arg3_t(-(1.0 - 0.98) / (0.98 * (1.0 - 0.98))),
        arg3_t(0.98),
        std::make_shared<LogLossFunction>(1.0),
    },
    {
        -log(0.58),
        arg3_t(-(1.0 - 0.58) / (0.58 * (1.0 - 0.58))),
        arg3_t(0.58),
        std::make_shared<LogLossFunction>(1.0),
    },
    // Sum function test cases
    {
        0.5,
        arg3_t(0.25),
        arg3_t(0),
        std::make_shared<SumFunction<double>>(
            std::vector<std::shared_ptr<BaseFunction<double>>>{
                std::make_shared<SigmoidFunction>()}),
    },
    {
        1.0,
        arg3_t(0.5),
        arg3_t(0),
        std::make_shared<SumFunction<double>>(
            std::vector<std::shared_ptr<BaseFunction<double>>>{
                std::make_shared<SigmoidFunction>(),
                std::make_shared<SigmoidFunction>(),
            }),
    },
    {
        2,
        arg3_t(1.0),
        arg3_t(0),
        std::make_shared<SumFunction<double>>(
            std::vector<std::shared_ptr<BaseFunction<double>>>{
                std::make_shared<SigmoidFunction>(),
                std::make_shared<SigmoidFunction>(),
            },
            2),
    },
};

TEST_P(FunctionValueTest3, function_test) {
  auto value = GetParam();

  EXPECT_EQ(value.f->function(value.argument), value.expected_function_value);
}

TEST_P(FunctionValueTest3, derivative_test) {
  auto value = GetParam();

  EXPECT_EQ(get_arg<0>(value.f->gradient(value.argument)),
            get_arg<0>(value.expected_derivative_value));
}

INSTANTIATE_TEST_SUITE_P(FunctionValue,
                         FunctionValueTest3,
                         testing::ValuesIn(f_value_test_cases3));
