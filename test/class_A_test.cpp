#include <gtest/gtest.h>

#include "nnoops/class_A.hpp"

using namespace nnoops;

TEST(ClassA, basic_test) {

EXPECT_EQ(class_A::sum(5, 6), 11);

}