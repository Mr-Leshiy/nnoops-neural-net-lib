#ifndef NNOOPS_LIB_CPP_FUNCTIONS_ARGUMENT_HPP_
#define NNOOPS_LIB_CPP_FUNCTIONS_ARGUMENT_HPP_

#include <stdio.h>

#include <string>
#include <type_traits>
#include <utility>

#include "nnoops/strutil.hpp"

namespace nnoops {

struct CheckPoint;

template <typename... Ts>
struct Argument {
  // operator*=

  Argument<Ts...>& operator*=(double) { return *this; }

  Argument<Ts...>& operator*=(const Argument<Ts...>&&) { return *this; }

  Argument<Ts...>& operator*=(const Argument<Ts...>&) { return *this; }

  // opearator+=

  Argument<Ts...>& operator+=(double) { return *this; }

  Argument<Ts...>& operator+=(const Argument<Ts...>&&) { return *this; }

  Argument<Ts...>& operator+=(const Argument<Ts...>&) { return *this; }

  // operator-=

  Argument<Ts...>& operator-=(double) { return *this; }

  Argument<Ts...>& operator-=(const Argument<Ts...>&&) { return *this; }

  Argument<Ts...>& operator-=(const Argument<Ts...>&) { return *this; }

  // operator==

  bool operator==(const Argument<Ts...>&&) const { return true; }

  bool operator==(const Argument<Ts...>&) const { return true; }

  // operator!=

  bool operator!=(const Argument<Ts...>&&) const { return true; }

  bool operator!=(const Argument<Ts...>&) const { return true; }

  friend std::string toPrettyString(const Argument<Ts...>&) { return ""; }
};

template <typename T, typename... Ts>
struct Argument<T, Ts...> : public Argument<Ts...> {
 private:
  using check_type =
      typename std::enable_if<std::is_integral<T>::value ||
                              std::is_floating_point<T>::value ||
                              std::is_base_of<CheckPoint, T>::value>::type;

 public:
  Argument(T arg, Ts... args) : Argument<Ts...>(args...), arg(arg) {}

  Argument<T, Ts...>& operator*=(double val) {
    this->arg *= val;
    Argument<Ts...>::operator*=(val);
    return *this;
  }

  Argument<T, Ts...>& operator*=(const Argument<T, Ts...>&& val) {
    this->arg *= std::move(val.arg);
    Argument<Ts...>::operator*=(val);
    return *this;
  }

  Argument<T, Ts...>& operator*=(const Argument<T, Ts...>& val) {
    this->arg *= val.arg;
    Argument<Ts...>::operator*=(val);
    return *this;
  }

  Argument<T, Ts...>& operator+=(double val) {
    this->arg += val;
    Argument<Ts...>::operator+=(val);
    return *this;
  }

  Argument<T, Ts...>& operator+=(const Argument<T, Ts...>&& val) {
    this->arg += std::move(val.arg);
    Argument<Ts...>::operator+=(val);
    return *this;
  }

  Argument<T, Ts...>& operator+=(const Argument<T, Ts...>& val) {
    this->arg += val.arg;
    Argument<Ts...>::operator+=(val);
    return *this;
  }

  Argument<T, Ts...>& operator-=(double val) {
    this->arg -= val;
    Argument<Ts...>::operator-=(val);
    return *this;
  }

  Argument<T, Ts...>& operator-=(const Argument<T, Ts...>&& val) {
    this->arg -= std::move(val.arg);
    Argument<Ts...>::operator-=(val);
    return *this;
  }

  Argument<T, Ts...>& operator-=(const Argument<T, Ts...>& val) {
    this->arg -= val.arg;
    Argument<Ts...>::operator-=(val);
    return *this;
  }

  // operator==

  bool operator==(const Argument<T, Ts...>&& val) const {
    return this->arg == val.arg && Argument<Ts...>::operator==(val);
  }

  bool operator==(const Argument<T, Ts...>& val) const {
    return this->arg == val.arg && Argument<Ts...>::operator==(val);
  }

  // operator!=
  bool operator!=(const Argument<T, Ts...>&& val) const {
    return this->arg != val.arg && Argument<Ts...>::operator==(val);
  }

  bool operator!=(const Argument<T, Ts...>& val) const {
    return this->arg != val.arg && Argument<Ts...>::operator==(val);
  }

  // operator*

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>&& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) *= val;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) *= val;
  }

  friend inline Argument<T, Ts...> operator*(double val,
                                             const Argument<T, Ts...>&& arg) {
    return Argument<T, Ts...>(arg) *= val;
  }

  friend inline Argument<T, Ts...> operator*(double val,
                                             const Argument<T, Ts...>& arg) {
    return Argument<T, Ts...>(arg) *= val;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) *= arg2;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) *= arg2;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) *= arg2;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) *= arg2;
  }

  // operator+

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>&& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) += val;
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) += val;
  }

  friend inline Argument<T, Ts...> operator+(double val,
                                             const Argument<T, Ts...>&& arg) {
    return Argument<T, Ts...>(arg) += val;
  }

  friend inline Argument<T, Ts...> operator+(double val,
                                             const Argument<T, Ts...>& arg) {
    return Argument<T, Ts...>(arg) += val;
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) += arg2;
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) += arg2;
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) += arg2;
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) += arg2;
  }

  // operator-

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>&& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) -= val;
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>& arg,
                                             double val) {
    return Argument<T, Ts...>(arg) -= val;
  }

  friend inline Argument<T, Ts...> operator-(double val,
                                             const Argument<T, Ts...>&& arg) {
    return Argument<T, Ts...>(arg) -= val;
  }

  friend inline Argument<T, Ts...> operator-(double val,
                                             const Argument<T, Ts...>& arg) {
    return Argument<T, Ts...>(arg) -= val;
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) -= arg2;
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) -= arg2;
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>&& arg1,
                                             const Argument<T, Ts...>& arg2) {
    return Argument<T, Ts...>(arg1) -= arg2;
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>& arg1,
                                             const Argument<T, Ts...>&& arg2) {
    return Argument<T, Ts...>(arg1) -= arg2;
  }

  friend std::string toPrettyString(const Argument<T, Ts...>& arg) {
    std::string result =
        toPrettyString(arg.arg) + "; " + toPrettyString(Argument<Ts...>(arg));

    return result;
  }

  T arg;
};

template <size_t k, typename>
struct ArgumentTypeHolder;

template <typename T, typename... Ts>
struct ArgumentTypeHolder<0, Argument<T, Ts...>> {
  using type = T;
};

template <size_t k, typename T, typename... Ts>
struct ArgumentTypeHolder<k, Argument<T, Ts...>> {
  using type = typename ArgumentTypeHolder<k - 1, Argument<Ts...>>::type;
};

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(Argument<Ts...>& arg) {
  return arg.arg;
}

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    const typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(const Argument<Ts...>& arg) {
  return arg.arg;
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if<
    k != 0,
    typename ArgumentTypeHolder<k, Argument<T, Ts...>>::type&>::type
get_arg(Argument<T, Ts...>& arg) {
  Argument<Ts...>& base = arg;
  return get_arg<k - 1>(base);
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if<
    k != 0,
    const typename ArgumentTypeHolder<k, Argument<T, Ts...>>::type&>::type
get_arg(const Argument<T, Ts...>& arg) {
  const Argument<Ts...>& base = arg;
  return get_arg<k - 1>(base);
}

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(Argument<Ts...>&& arg) {
  return arg.arg;
}

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    const typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(const Argument<Ts...>&& arg) {
  return arg.arg;
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if<
    k != 0,
    typename ArgumentTypeHolder<k, Argument<T, Ts...>>::type&>::type
get_arg(Argument<T, Ts...>&& arg) {
  Argument<Ts...>& base = arg;
  return get_arg<k - 1>(base);
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if<
    k != 0,
    const typename ArgumentTypeHolder<k, Argument<T, Ts...>>::type&>::type
get_arg(const Argument<T, Ts...>&& arg) {
  const Argument<Ts...>& base = arg;
  return get_arg<k - 1>(base);
}

}  // namespace nnoops

#endif
