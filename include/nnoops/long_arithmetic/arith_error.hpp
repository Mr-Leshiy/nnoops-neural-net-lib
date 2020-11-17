#ifndef NNOOPS_LIB_CPP_LONG_ARITHMETIC_ARITH_ERROR_HPP_
#define NNOOPS_LIB_CPP_LONG_ARITHMETIC_ARITH_ERROR_HPP_

#include <stdexcept>
#include <string>

namespace nnoops {

struct arith_error : public std::runtime_error {
  explicit arith_error(const std::string& err) : std::runtime_error(err) {}
  explicit arith_error(const std::string& err, const std::string& debug)
      : std::runtime_error(err + " : " + debug) {}
};

}  // namespace nnoops

#define THROW_ARITH_ERROR(x, ...) \
  if (!(x)) throw nnoops::arith_error(__VA_ARGS__);

#endif