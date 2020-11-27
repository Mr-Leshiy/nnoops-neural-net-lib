#include <gtest/gtest.h>

#include "nnoops/strutil.hpp"

using namespace nnoops;

TEST(StrUtil, hex_test) {
  std::vector<uint8_t> data1 = {32, 65, 123, 54, 12, 190};
  std::string hex_str = HexStr(data1);

  EXPECT_EQ(hex_str, "20417b360cbe");

  std::vector<uint8_t> data2 = ParseHex<uint8_t>(hex_str);

  EXPECT_EQ(data1, data2);

  data1 = {0, 0, 0, 0, 0, 32, 65, 123, 54, 12, 190};
  hex_str = HexStr(data1);

  EXPECT_EQ(hex_str, "000000000020417b360cbe");

  std::vector<uint32_t> data3 = {0, 321454321};

  hex_str = HexStr(data3);
  EXPECT_EQ(hex_str, "00000000132900f1");

  std::vector<uint32_t> data4 = ParseHex<uint32_t>(hex_str);

  EXPECT_EQ(data3, data4);
}

TEST(StrUtil, removeZeros_test) {
  EXPECT_EQ(removeZeros("000000000020417b360cbe"), "20417b360cbe");
  EXPECT_EQ(removeZeros("000000000043141fade134"), "43141fade134");
  EXPECT_EQ(removeZeros("0000000000000000000000"), "0");
}
