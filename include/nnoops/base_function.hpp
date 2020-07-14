#ifndef NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_
#define NNOOPS_LIB_CPP_BASE_FUNCTION_HPP_

namespace nnoops {

struct BaseFunction {
  virtual ~BaseFunction() = default;

  virtual double function(double x) = 0;
  virtual double derivative(double x) = 0;
};

}  // namespace nnoops

#endif