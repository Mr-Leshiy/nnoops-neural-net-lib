#ifndef NNOOPS_LIB_CPP_FUNCTIONS_UTILS_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_UTILS_HPP_

#include <stdint.h>

#include <string>

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

}  // namespace nnoops
#endif