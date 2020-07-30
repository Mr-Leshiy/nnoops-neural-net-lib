#include <gtest/gtest.h>

#include "nnoops/functions/argument.hpp"
#include "nnoops/functions/point.hpp"

using namespace nnoops;

TEST(Argument, Basic_test) {
  Point<2> p = {4, 6};

  Argument<double, int, Point<2>> arg = {52.432, 6, p};

  EXPECT_EQ(get_arg<0>(arg), 52.432);
  EXPECT_EQ(get_arg<1>(arg), 6);
  EXPECT_EQ(get_arg<2>(arg), p);
}

TEST(Argument, Operations_methods_test) {
  Point<2> p = {4, 6};

  Argument<double, int, Point<2>> arg = {50, 12, p};

  arg *= 2;

  p = {8, 12};
  EXPECT_EQ(get_arg<0>(arg), 100);
  EXPECT_EQ(get_arg<1>(arg), 24);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg += 10;

  p = {18, 22};
  EXPECT_EQ(get_arg<0>(arg), 110);
  EXPECT_EQ(get_arg<1>(arg), 34);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg -= 20;

  p = {-2, 2};
  EXPECT_EQ(get_arg<0>(arg), 90);
  EXPECT_EQ(get_arg<1>(arg), 14);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = arg + 20;

  p = {18, 22};
  EXPECT_EQ(get_arg<0>(arg), 110);
  EXPECT_EQ(get_arg<1>(arg), 34);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = arg - 20;

  p = {-2, 2};
  EXPECT_EQ(get_arg<0>(arg), 90);
  EXPECT_EQ(get_arg<1>(arg), 14);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = 20 + arg;

  p = {18, 22};
  EXPECT_EQ(get_arg<0>(arg), 110);
  EXPECT_EQ(get_arg<1>(arg), 34);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = 20 - arg;

  p = {-2, 2};
  EXPECT_EQ(get_arg<0>(arg), 90);
  EXPECT_EQ(get_arg<1>(arg), 14);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = arg * 2;

  p = {-4, 4};
  EXPECT_EQ(get_arg<0>(arg), 180);
  EXPECT_EQ(get_arg<1>(arg), 28);
  EXPECT_EQ(get_arg<2>(arg), p);

  arg = 2 * arg;

  p = {-8, 8};
  EXPECT_EQ(get_arg<0>(arg), 360);
  EXPECT_EQ(get_arg<1>(arg), 56);
  EXPECT_EQ(get_arg<2>(arg), p);
}

TEST(Argument, Operations_between_two_arguments) {
  Argument<double, double> arg1 = {4, 10};
  Argument<double, double> arg2 = {4, 10};

  arg1 = arg1 + arg1;
  arg2 += arg2;

  EXPECT_EQ(get_arg<0>(arg1), get_arg<0>(arg2));
  EXPECT_EQ(get_arg<1>(arg1), get_arg<1>(arg2));

  arg1 -= Argument<double, double>{4, 10};
  arg2 = arg2 - Argument<double, double>{4, 10};

    EXPECT_EQ(get_arg<0>(arg1), get_arg<0>(arg2));
    EXPECT_EQ(get_arg<1>(arg1), get_arg<1>(arg2));
}
