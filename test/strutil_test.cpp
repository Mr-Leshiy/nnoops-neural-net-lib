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

  std::vector<uint16_t> data3 = {0, 12415};

  hex_str = HexStr(data3);
  EXPECT_EQ(hex_str, "0000307f");

  std::vector<uint16_t> data4 = ParseHex<uint16_t>(hex_str);

  EXPECT_EQ(data3, data4);

  std::vector<uint32_t> data5 = {0, 321454321};

  hex_str = HexStr(data5);
  EXPECT_EQ(hex_str, "00000000132900f1");

  std::vector<uint32_t> data6 = ParseHex<uint32_t>(hex_str);

  EXPECT_EQ(data5, data6);
}

TEST(StrUtil, HexToDec_test) {
  EXPECT_EQ(HexToDec("20417b360cbe"), "35465612102846");

  EXPECT_EQ(HexToDec("4125feb3c"), "17488145212");

  EXPECT_EQ(HexToDec("bce4551ff"), "50705289727");

  EXPECT_EQ(HexToDec("fad314bc"), "4208137404");
}

TEST(StrUtil, DecToHex_test) {
  EXPECT_EQ(DecToHex("35465612102846"), "20417b360cbe");

  EXPECT_EQ(DecToHex("17488145212"), "4125feb3c");

  EXPECT_EQ(DecToHex("50705289727"), "bce4551ff");

  EXPECT_EQ(DecToHex("4208137404"), "fad314bc");
}

TEST(StrUtil, removeZeros_test) {
  EXPECT_EQ(removeZeros("000000000020417b360cbe"), "20417b360cbe");
  EXPECT_EQ(removeZeros("000000000043141fade134"), "43141fade134");
  EXPECT_EQ(removeZeros("0000000000000000000000"), "0");
}
