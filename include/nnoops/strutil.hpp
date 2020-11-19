#ifndef NNOOPS_LIB_CPP_STRUTIL_HPP_
#define NNOOPS_LIB_CPP_STRUTIL_HPP_

#include <string>
#include <vector>

namespace nnoops {

inline std::string toPrettyString(const uint64_t& val) {
  return std::to_string(val);
}

inline std::string toPrettyString(const double& val) {
  return std::to_string(val);
}

inline std::string toPrettyString(const int64_t& val) {
  return std::to_string(val);
}

bool IsHex(const std::string& str);
std::vector<uint8_t> ParseHex(const char* psz);
std::vector<uint8_t> ParseHex(const std::string& hex);

constexpr inline bool IsSpace(char c) noexcept {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}

template <typename T>
std::string HexStr(const T& itbegin, const T& itend) {
  std::string rv;
  // clang-format off
    static const char hexmap[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
  // clang-format on
  rv.reserve(std::distance(itbegin, itend) * 2u);
  for (T it = itbegin; it < itend; ++it) {
    uint8_t val = (uint8_t)(*it);
    rv.push_back(hexmap[val >> 4u]);
    rv.push_back(hexmap[val & 15u]);
  }
  return rv;
}

template <typename T>
std::string HexStr(const T& vch) {
  return HexStr(vch.begin(), vch.end());
}

// remove all '0' char, before to the first non '0' char
std::string removeZeros(const std::string& str);

std::vector<uint8_t> toBytes(const std::string& input);

}  // namespace nnoops

#endif
