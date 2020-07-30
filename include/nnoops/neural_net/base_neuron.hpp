#ifndef NNOOPS_LIB_CPP_NEURAL_NET_BASE_NEURON_HPP_
#define NNOOPS_LIB_CPP_NEURAL_NET_BASE_NEURON_HPP_

#include "nnoops/functions/base_function.hpp"

namespace nnoops {

struct BaseNeuron {
  virtual ~BaseNeuron() = 0;
};

}  // namespace nnoops

#endif