#ifndef NNOOPS_LIB_CPP_ARGUMENT_HPP_
#define NNOOPS_LIB_CPP_ARGUMENT_HPP_

#include <stdio.h>

#include <type_traits>

namespace nnoops {

struct CheckPoint;

template <typename... Ts>
struct Argument {
  Argument<Ts...>& operator*=(double) { return *this; }

  Argument<Ts...>& operator+=(double) { return *this; }

  Argument<Ts...>& operator-=(double) { return *this; }
};

template <typename T, typename... Ts>
struct Argument<T, Ts...> : public Argument<Ts...> {
  using type =
      typename std::enable_if<std::is_integral<T>::value ||
                              std::is_floating_point<T>::value ||
                              std::is_base_of<CheckPoint, T>::value>::type;

  Argument(T arg, Ts... args) : Argument<Ts...>(args...), arg(arg) {}

  Argument<T, Ts...>& operator*=(double val) {
    this->arg *= val;
    Argument<Ts...>::operator*=(val);
    return *this;
  }

  Argument<T, Ts...>& operator+=(double val) {
    this->arg += val;
    Argument<Ts...>::operator+=(val);
    return *this;
  }

  Argument<T, Ts...>& operator-=(double val) {
    this->arg -= val;
    Argument<Ts...>::operator-=(val);
    return *this;
  }

  friend inline Argument<T, Ts...> operator*(const Argument<T, Ts...>& arg,
                                             double val) {
    return std::move(Argument<T, Ts...>(arg) *= val);
  }

  friend inline Argument<T, Ts...> operator+(const Argument<T, Ts...>& arg,
                                             double val) {
    return std::move(Argument<T, Ts...>(arg) += val);
  }

  friend inline Argument<T, Ts...> operator-(const Argument<T, Ts...>& arg,
                                             double val) {
    return std::move(Argument<T, Ts...>(arg) -= val);
  }

  friend inline Argument<T, Ts...> operator*(double val,
                                             const Argument<T, Ts...>& arg) {
    return std::move(Argument<T, Ts...>(arg) *= val);
  }

  friend inline Argument<T, Ts...> operator+(double val,
                                             const Argument<T, Ts...>& arg) {
    return std::move(Argument<T, Ts...>(arg) += val);
  }

  friend inline Argument<T, Ts...> operator-(double val,
                                             const Argument<T, Ts...>& arg) {
    return std::move(Argument<T, Ts...>(arg) -= val);
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
