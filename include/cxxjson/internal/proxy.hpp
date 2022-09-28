#ifndef CXXJSON_INTERNAL_PROXY_HPP
#define CXXJSON_INTERNAL_PROXY_HPP

#include <concepts>
#include <type_traits>
#include <tuple>
#include <utility>
#include <typeinfo>

namespace cxxjson::internal {
  enum class constraint_level { none, nontrivial, nothrow, trivial };
  
  template <class T, auto F> struct dispatch;
  
  template <class R, class... Args, auto F>
  struct dispatch<R(Args...), F> {
    using return_type = R;
    using argument_type = std::tuple<Args...>;
    static constexpr auto invoker = F;
    dispatch() = delete;
  };
 
  template <class... Ds>
  struct facade {
    using dispatches = std::tuple<Ds...>;
    static constexpr size_t max_size = 2U * sizeof(void);
    static constexpr size_t max_aligment = alignof(void(*));
    static constexpr constraint_level min_copyability = constraint_level::none;
    static constexpr constraint_level min_relocatability = constraint_level::nothrow;
    static constexpr constraint_level min_destructibility = constraint_level::nothrow;
    facade() = delete;
  };
 
  class bad_proxy_cast :public std::bad_cast {
  public:
    const char* what() const noexcept override { return "Bad proxy cast"; };
  };
 
  template <class P, class F>
  concept proxy_trait ;
  
  template <class F> requires see below
  class proxy;
 
  template <class F, class T, class... Args>
  proxy<F> make_proxy(Args&&... args);
  
  template <class F, class T, class U, class... Args>
  proxy<F> make_proxy(initializer_list<U> il, Args&&... args);
 
  template <class F, class T>
  proxy<F> make_proxy(T&& value);
  
  template <class F>
  void swap(std::proxy<F>& a, std::proxy<F>& b)
  noexcept(see below) requires(see below);
}

}

#endif