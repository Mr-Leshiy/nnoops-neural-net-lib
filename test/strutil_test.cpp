#include <gtest/gtest.h>

#include "nnoops/strutil.hpp"

using namespace nnoops;

TEST(StrUtil, basic_test) {
  std::vector<uint8_t> data = {32, 65, 123, 54, 12, 190};
  std::string hex_str = HexStr(data);

  EXPECT_EQ(hex_str, "20417b360cbe");

  std::vector<uint8_t> data2 = ParseHex(hex_str);

  EXPECT_EQ(data, data2);
}