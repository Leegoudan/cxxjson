#pragma once
#ifndef CXXJSON_INTERNAL_SIZE_T_LITERAL_HPP
#define CXXJSON_INTERNAL_SIZE_T_LITERAL_HPP

#include <concepts>

namespace cxxjson::internal {
  constexpr std::size_t operator""zu(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""zU(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""Zu(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""ZU(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""uz(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""uZ(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""Uz(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
  constexpr std::size_t operator""UZ(unsigned long long int arg) { return static_cast<std::size_t>(arg); }
}

#endif