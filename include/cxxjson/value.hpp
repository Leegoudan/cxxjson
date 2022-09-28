#pragma once
#ifndef CXXJSON_VALUE_HPP
#define CXXJSON_VALUE_HPP

#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <variant>
#include <concepts>
#include <memory_resource>

namespace cxxjson {
  enum class value_type {
    null_t,
    false_t,
    true_t,
    number_signed,
    number_unsigned,
    number_float,
    object,
    array,
    string
  };

  class value;

  struct normal_growth_policy {
    normal_growth_policy() : init(8) {}
  protected:
    normal_growth_policy(std::size_t i_) : init(i_) {}
    static std::size_t grow_up(std::size_t src) {
      return src + (src >> 1);
    }
  private:
    std::size_t init;
  };

  struct fast_growth_policy : public normal_growth_policy {
    fast_growth_policy() : normal_growth_policy(8) {}
  protected:
    fast_growth_policy(std::size_t i_) : normal_growth_policy(i_) {}
    static std::size_t grow_up(std::size_t src) {
      return (src << 1);
    }
  };

  struct big_fast_growth_policy : public fast_growth_policy {
    big_fast_growth_policy() : fast_growth_policy(1024*10) {}
  };

  template<typename F> requires std::is_same_v<std::invoke_result_t<F, std::size_t>, std::size_t>
  struct customize_growth_policy : public normal_growth_policy {
    customize_growth_policy(std::size_t i_) : normal_growth_policy(i_) {}
  protected:
    static std::size_t grow_up(std::size_t src) {
      return F()(src);
    }
  };

  // no thread-safety
  class pool_resource : public std::pmr::memory_resource {
  public:
    //ctor
    pool_resource() = default;

    pool_resource(normal_growth_policy policy, std::pmr::memory_resource* const upstream) noexcept
      : _policy(policy), _resource(upstream) {}
    explicit pool_resource(std::pmr::memory_resource* const upstream) noexcept : _resource{ upstream } {}
    explicit pool_resource(normal_growth_policy& policy) noexcept : _policy(policy) {}
    
    //dector
    virtual ~pool_resource() noexcept override { release(); }

    memory_resource* upstream_resource() const noexcept { return _resource; }


    void release() {}

    // delete
    pool_resource(const pool_resource&) = delete;
    pool_resource& operator=(const pool_resource&) = delete;

  private:
    void* do_allocate(std::size_t bytes, std::size_t align) {}
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t align) {}
    bool do_is_equal(const memory_resource& _That) const noexcept {
      return this == &_That;
    }

    normal_growth_policy _policy;
    std::pmr::memory_resource* _resource = std::pmr::get_default_resource();
  };

  class value final {
    struct null_t {};
    struct false_t { operator bool() const noexcept { return false; } };
    struct true_t : public false_t { operator bool() const noexcept { return true; } };
  
    using integral_t = long long; // __int128_t
    using floating_t = long double;
    using string_t = std::pmr::u8string;
    using key_t = std::u8string_view;
    using array_t = std::pmr::vector<value>;
    using object_t = std::pmr::map<key_t, value>;
    using variant_t = std::variant<null_t, false_t, true_t,
                                   integral_t, floating_t,
                                   string_t,
                                   array_t,
                                   object_t
                                  >;
    using variant_alloc = std::pmr::polymorphic_allocator<variant_t>;
  public:

    // ctor
    value() : _v(null_t{}) {}
    value(const value&) = default;
    value(value&&) = default;

    value(null_t) : _v(null_t{}) {}
    value(false_t) : _v(false_t{}) {}
    value(true_t) : _v(true_t{}) {}

    explicit value(bool b) {}

    template<std::integral T>
    explicit value(T t) : _v(static_cast<integral_t>(t)) {}

    template<std::floating_point T>
    explicit value(T t) : _v(static_cast<floating_t>(t)) {}

    template<typename CharT> requires requires(CharT) { sizeof(CharT) == sizeof(char8_t);  }
    explicit value (const std::basic_string<CharT>& s) : _v(string_t(s.begin(), s.end())) {}

    template<typename CharT> requires requires(CharT) { sizeof(CharT) == sizeof(char8_t);  }
    explicit value (std::basic_string<CharT>&& s) : _v(string_t(s.begin(), s.end())) {}

    // dtor
    ~value() = default;

    //operator=
    value& operator=(value rhs) {
      std::swap(_v, rhs._v);
    }

    template<typename T> requires std::is_arithmetic_v<std::remove_cvref_t<T>>
    value& operator=(T&& t) {
      std::swap(_v, vallue(t));
    }

    template<typename CharT> requires requires(CharT) { sizeof(CharT) == sizeof(char8_t);  }
    value& operator=(const std::basic_string<CharT>& s) {
      std::swap(_v, vallue(s));
    }

    template<typename CharT> requires requires(CharT) { sizeof(CharT) == sizeof(char8_t);  }
    value& operator=(std::basic_string<CharT>&& s) {
      std::swap(_v, vallue(s));
    }

    [[nodiscard]] value_type type() const noexcept {
      return static_cast<value_type>(_v.index());
    }

    template<typename T>
    T get() const {
      if (std::holds_alternative<T>(_v)) {
        return std::get<T>(_v); 
      }
    }

    [[nodiscard]] bool get_bool() const {
      if (std::holds_alternative<true_t>(_v)) {
        return true;
      }

      return false;
    }
    [[nodiscard]] int get_int() const {
      return static_cast<int>(std::get<long long>(_v));
    }
    [[nodiscard]] unsigned int get_uint() const {
      return static_cast<unsigned int>(std::get<long long>(_v));
    }
    [[nodiscard]] long long get_num() const {
      return std::get<long long>(_v);
    }
    [[nodiscard]] double get_double() const {
      return std::get<double>(_v);
    }

  private:
    variant_t _v;
    variant_alloc _alloc;
  };
}

#endif