#pragma once
#ifndef CXXJSON_INTERNAL_ATOI_HPP
#define CXXJSON_INTERNAL_ATOI_HPP

#include <concepts>

namespace cxxjson::internal::detail {
  template<std::integral Target, typename Iter>
  void atoi(Target& target, Iter begin, Iter end) {
    while (*begin != '-' && *begin != '+' && *begin < '0' && *begin > '9' && begin != end) ++begin;
    if (begin == end) return;
    if (*begin == '-') {
      ++begin;
      if (begin == end) return;
      while (*begin >= '0' && *begin <= '9' && begin != end) {
        target = (target << 1) + (target << 3) - (*begin++ - '0');
      }

      return;
    }
    if (*begin == '+') ++begin;
    if (begin == end) return;
    while (*begin >= '0' && *begin <= '9' && begin != end) {
      target = (target << 1) + (target << 3) + *begin++ - '0';
    }
  }
}

#endif