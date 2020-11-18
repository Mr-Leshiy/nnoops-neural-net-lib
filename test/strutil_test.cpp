#include <gtest/gtest.h>

#include "nnoops/strutil.hpp"

using namespace nnoops;

TEST(StrUtil, hex_test) {
  std::vector<uint8_t> data = {32, 65, 123, 54, 12, 190};
  std::string hex_str = HexStr(data);

  EXPECT_EQ(hex_str, "20417b360cbe");

  std::vector<uint8_t> data2 = ParseHex(hex_str);

  EXPECT_EQ(data, data2);

  data = {0, 0, 0, 0, 0, 32, 65, 123, 54, 12, 190};
  hex_str = HexStr(data);

  EXPECT_EQ(hex_str, "000000000020417b360cbe");
}

TEST(StrUtil, removeZeros_test) {
  EXPECT_EQ(removeZeros("000000000020417b360cbe"), "20417b360cbe");
  EXPECT_EQ(removeZeros("000000000043141fade134"), "43141fade134");
  EXPECT_EQ(removeZeros("0000000000000000000000"), "0");
}
