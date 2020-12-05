#ifndef NNOOPS_LIB_CPP_STRUTIL_HPP_
#define NNOOPS_LIB_CPP_STRUTIL_HPP_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace nnoops {

bool IsHex(const std::string& str);

bool IsDec(const std::string& str);

signed char GetDigit(uint8_t c);

struct str_error : public std::runtime_error {
  explicit str_error(const std::string& err) : std::runtime_error(err) {}
  explicit str_error(const std::string& err, const std::string& debug)
      : std::runtime_error(err + " : " + debug) {}
};

}  // namespace nnoops

#define THROW_STR_ERROR(x, ...) \
  if (!(x)) throw nnoops::str_error(__VA_ARGS__);

namespace {

// clang-format off
    static const char hexmap[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
// clang-format on

template <typename T,
          typename = typename std::enable_if<std::is_integral<T>::value &&
                                             std::is_unsigned<T>::value>::type>
void insert_hex_digits(T val, std::string& result) {
  int size = sizeof(val);
  static const T a = 0xfu;

  for (int i = size * 2 - 1; i >= 0; --i) {
    result.push_back(hexmap[(val & (a << (4u * i))) >> (4u * i)]);
  }
}

template <typename T>
const char* fillDigit(const char* psz, std::vector<T>& vch) {
  size_t size = sizeof(T);
  T n = 0;
  for (int32_t i = (int32_t)(size * 2 - 1); i >= 0; --i) {
    signed char c = nnoops::GetDigit(*psz++);
    if (c == (int8_t)-1) {
      return nullptr;
    }
    n |= c << (i * 4u);
  }
  vch.push_back(n);
  return psz;
}

}  // namespace

namespace nnoops {

constexpr inline bool IsSpace(char c) noexcept {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}

inline std::string toPrettyString(const uint64_t& val) {
  return std::to_string(val);
}

inline std::string toPrettyString(const double& val) {
  return std::to_string(val);
}

inline std::string toPrettyString(const int64_t& val) {
  return std::to_string(val);
}

template <typename T,
          typename = typename std::enable_if<std::is_integral<T>::value &&
                                             std::is_unsigned<T>::value>::type>
std::vector<T> ParseHex(const std::string& hex) {
  THROW_STR_ERROR(IsHex(hex), "provided not a hex str");
  // convert hex dump to vector
  const char* psz = hex.c_str();
  std::vector<T> vch;
  while (true) {
    psz = fillDigit(psz, vch);
    if (psz == nullptr) {
      break;
    }
  }
  return vch;
}

template <typename T>
std::string HexStr(const T& itbegin, const T& itend) {
  std::string rv;
  rv.reserve(std::distance(itbegin, itend) * 2u);
  for (T it = itbegin; it < itend; ++it) {
    insert_hex_digits(*it, rv);
  }
  return rv;
}

template <typename T>
std::string HexStr(const T& vch) {
  return HexStr(vch.begin(), vch.end());
}

// convert hex string to decimal string
// "ff" => "255"
std::string HexToDec(std::string hex);

// convert decimal string to hex string
// "255" => "ff"
std::string DecToHex(std::string dec);

// remove all '0' char, before to the first non '0' char
std::string removeZeros(const std::string& str);

std::vector<uint8_t> toBytes(const std::string& input);

}  // namespace nnoops

#endif
