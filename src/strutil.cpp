#include "nnoops/strutil.hpp"

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

signed char HexDigit(char c) { return p_util_hexdigit[(unsigned char)c]; }

template <typename T>
const char* fillDigit(const char* psz, std::vector<T>& vch) {
  size_t size = sizeof(T);
  T n = 0;
  for (int32_t i = (int32_t)(size * 2 - 1); i >= 0; --i) {
    signed char c = HexDigit(*psz++);
    if (c == (int8_t)-1) {
      return nullptr;
    }
    n |= c << (i * 4u);
  }
  vch.push_back(n);
  return psz;
}

template <>
std::vector<uint8_t> ParseHex(const char* psz) {
  // convert hex dump to vector
  std::vector<uint8_t> vch;
  while (true) {
    while (IsSpace(*psz)) {
      psz++;
    }
    psz = fillDigit(psz, vch);
    if (psz == nullptr) {
      break;
    }
  }
  return vch;
}

template <>
std::vector<uint32_t> ParseHex(const char* psz) {
  // convert hex dump to vector
  std::vector<uint32_t> vch;
  while (true) {
    while (IsSpace(*psz)) {
      psz++;
    }
    psz = fillDigit(psz, vch);
    if (psz == nullptr) {
      break;
    }
  }
  return vch;
}

template <>
std::vector<uint8_t> ParseHex(const std::string& hex) {
  return ParseHex<uint8_t>(hex.c_str());
}

template <>
std::vector<uint32_t> ParseHex(const std::string& hex) {
  return ParseHex<uint32_t>(hex.c_str());
}

bool IsHex(const std::string& str) {
  for (char it : str) {
    if (HexDigit(it) < 0) {
      return false;
    }
  }

  return (!str.empty()) && (str.size() % 2 == 0);
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
