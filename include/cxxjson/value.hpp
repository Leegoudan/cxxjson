#pragma once
#ifndef CXXJSON_VALUE_HPP
#define CXXJSON_VALUE_HPP

#include <concepts>
#include <map>
#include <memory_resource>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "internal/pool_resource.hpp"

namespace cxxjson {
  enum class value_type {
    null_t,
    false_t,
    true_t,
    number_integral,
    number_float,
    string,
    array,
    object
  };

  class value final {
    struct null_t {};
    struct false_t {
      operator bool() const noexcept { return false; }
    };
    struct true_t : public false_t {
      operator bool() const noexcept { return true; }
    };

    using integral_t = long long;
    using unsigned_integral_t = unsigned long long;
    using floating_t = double;
    using string_t = std::u8string_view;
    using key_t = string_t;
    using array_t = std::pmr::vector<value>;
    using object_t = std::pmr::map<key_t, value>;
    using variant_t = std::variant<null_t, false_t, true_t, integral_t, unsigned_integral_t,
                                   floating_t, string_t, array_t, object_t>;

  public:
    // ctor
    value() : _v(null_t{}) {}
    value(const value&) = default;
    value(value&&) = default;

    value(null_t) : _v(null_t{}) {}
    value(false_t) : _v(false_t{}) {}
    value(true_t) : _v(true_t{}) {}

    explicit value(bool b) {}

    template <std::integral T>
    explicit value(T t) : _v(static_cast<integral_t>(t)) {}

    template <std::floating_point T>
    explicit value(T t) : _v(static_cast<floating_t>(t)) {}

    template <typename CharT>
    requires requires(CharT) { sizeof(CharT) == sizeof(char8_t); }
    explicit value(const std::basic_string<CharT>& s) : _v(string_t(s.begin(), s.end())) {}

    template <typename CharT>
    requires requires(CharT) { sizeof(CharT) == sizeof(char8_t); }
    explicit value(std::basic_string<CharT>&& s) : _v(string_t(s.begin(), s.end())) {}

    // dtor
    ~value() = default;

    // operator=
    value& operator=(value rhs) { std::swap(_v, rhs._v); }

    template <typename T>
    requires std::is_arithmetic_v<std::remove_cvref_t<T>> value& operator=(T&& t) {
      std::swap(_v, vallue(t));
    }

    template <typename CharT>
    requires requires(CharT) { sizeof(CharT) == sizeof(char8_t); }
    value& operator=(const std::basic_string<CharT>& s) { std::swap(_v, value(s)); }

    template <typename CharT>
    requires requires(CharT) { sizeof(CharT) == sizeof(char8_t); }
    value& operator=(std::basic_string<CharT>&& s) { std::swap(_v, value(s)); }

    [[nodiscard]] value_type type() const noexcept { return static_cast<value_type>(_v.index()); }

    template <typename T>
    T get() const {
      if (std::holds_alternative<T>(_v)) {
        return std::get<T>(_v);
      }
    }

  private:
    variant_t _v;
  };
} // namespace cxxjson

#endif