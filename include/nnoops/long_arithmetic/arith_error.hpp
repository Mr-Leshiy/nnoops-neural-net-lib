#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_ARITH_ERROR_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_ARITH_ERROR_HPP_

#include <stdexcept>
#include <string>

namespace nnoops {

struct arith_error : public std::runtime_error {
  explicit arith_error(const std::string& err) : std::runtime_error(err) {}
};

}  // namespace nnoops

#endif