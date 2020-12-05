#include "nnoops/strutil.hpp"

namespace {

std::string dec2base(uint8_t base, uint8_t value) {
  std::string rv;

  do {
    rv.push_back(::hexmap[value % base]);
    value /= base;
  } while (value > 0);

  std::reverse(rv.begin(), rv.end());
  return rv;
}

uint8_t base2dec(uint8_t base, const std::string& value) {
  uint8_t rv = 0;
  for (size_t i = 0; i < value.size(); ++i) {
    rv *= base;
    int c = nnoops::HexDigit(value[i]);
    if (c < 0 || c >= base) {
      // TODO throw exception
      return 0;
    }
    rv += (uint8_t)c;
  }

  return rv;
}

uint8_t divide(std::string& x, uint8_t base_to, uint8_t base_from) {
  std::string quotient = "";

  size_t size = x.size();

  for (size_t i = 0; i < size; ++i) {
    size_t j = i + 1 + x.size() - size;
    if (x.size() < j) break;

    uint8_t value = base2dec(base_from, x.substr(0, j));
    quotient.push_back(::hexmap[value / base_to]);
    x = dec2base(base_from, value % base_to) + x.substr(j);
  }

  uint8_t remainder = base2dec(base_from, x);

  x = nnoops::removeZeros(quotient);

  return remainder;
}

}  // namespace

namespace nnoops {

static const signed char p_util_hexdigit[256] = {
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    0,  1,   2,   3,   4,   5,   6,   7,  8,  9,  -1, -1, -1, -1, -1, -1,
    -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

signed char HexDigit(uint8_t c) { return p_util_hexdigit[c]; }

bool IsHex(const std::string& str) {
  for (char it : str) {
    if (HexDigit(it) < 0) {
      return false;
    }
  }

  return (!str.empty());
}

std::string HexToDec(std::string hex) {
  std::string rv = "";

  if (!IsHex(hex)) {
    // TODO throw exception
    return "";
  }

  do {
    uint8_t remainder = divide(hex, 10, 16);
    rv.push_back(::hexmap[remainder]);
  } while (!hex.empty() && !(hex.size() == 1 && hex[0] == '0'));

  std::reverse(rv.begin(), rv.end());
  return rv;
}

std::string DecToHex(std::string dec) {
  std::string rv = "";

  // TODO add IsDec function
  /*if (!IsHes(hex)) {
    // TODO throw exception
    return "";
  } */

  do {
    uint8_t remainder = divide(dec, 16, 10);
    rv.push_back(::hexmap[remainder]);
  } while (!dec.empty() && !(dec.size() == 1 && dec[0] == '0'));

  std::reverse(rv.begin(), rv.end());
  return rv;
}

std::string removeZeros(const std::string& str) {
  auto it = str.begin();
  auto end = --str.end();
  for (; it != end && (char)*it == '0'; ++it) {
  }
  return std::string(it, str.end());
}

std::vector<uint8_t> toBytes(const std::string& str) {
  return std::vector<uint8_t>(str.begin(), str.end());
}

}  // namespace nnoops
