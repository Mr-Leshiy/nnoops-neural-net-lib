#ifndef NNOOPS_LIB_CPP_ARGUMENT_HPP_
#define NNOOPS_LIB_CPP_ARGUMENT_HPP_

#include <tuple>

namespace nnoops {

template <typename... Ts>
struct Argument {
  uint32_t args_numnber;
};

template <typename T, typename... Ts>
struct Argument<T, Ts...> : public Argument<Ts...> {
  Argument(T arg, Ts... args) : Argument<Ts...>(args...), arg(arg) {
    ++this->args_numnber;
  }

  T arg;
};

template <size_t, typename>
struct ArgumentTypeHolder;

template <typename T, typename... Ts>
struct ArgumentTypeHolder<0, Argument<T, Ts...>> {
  using type = T;
};

template <size_t k, typename T, typename... Ts>
struct ArgumentTypeHolder<k, Argument<T, Ts...>> {
  using type = typename ArgumentTypeHolder<k - 1, Argument<T, Ts...>>::type;
};

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(Argument<Ts...>& arg) {
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

template <size_t k, typename... Ts>
typename std::enable_if<
    k == 0,
    typename ArgumentTypeHolder<0, Argument<Ts...>>::type&>::type
get_arg(Argument<Ts...>&& arg) {
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

}  // namespace nnoops

#endif
