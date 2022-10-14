#pragma once
#ifndef CXXJSON_INTERNAL_POOL_RESOURCE_HPP
#define CXXJSON_INTERNAL_POOL_RESOURCE_HPP

#include <memory_resource>
#include "size_t_literal.hpp"

namespace cxxjson::internal {

  template <typename F, std::size_t N>
  requires std::is_same_v<std::invoke_result_t<decltype(F()), std::size_t>, std::size_t>
  struct customize_growth_policy : private F {
    constexpr static std::size_t init_size = N;
    static std::size_t grow_up(std::size_t src) { return std::invoke(F(), src); }
  };

  template <std::size_t N = 0>
  struct normal_growth_policy
      : protected customize_growth_policy<
            decltype([](std::size_t len) { return len + ((len + 1) >> 1); }), N> {};

  template <std::size_t N = 8>
  struct fast_growth_policy
      : protected customize_growth_policy<decltype([](std::size_t len) { return (len << 1); }), N> {
  };

  template <std::size_t N = 1024 * 8>
  struct big_fast_growth_policy : protected fast_growth_policy<N> {};

  // no thread-safety
  template <typename policy>
  class pool_resource : public std::pmr::memory_resource, private policy {
    using pool_type = std::pmr::vector<std::byte>;

  public:
    // ctor
    pool_resource() {
      _pools.emplace_back(pool_type{});
      _pools.emplace_back(pool_type{});
      _pools[0].reserve(policy::init_size);
    }

    explicit pool_resource(std::pmr::memory_resource* const upstream) noexcept {
      _pools.emplace_back(pool_type(upstream));
      _pools.emplace_back(pool_type(upstream));
      _pools[0].reserve(policy::init_size);
    }

    // dector
    virtual ~pool_resource() noexcept override = default;

    memory_resource* upstream_resource() const noexcept {
      return _pools[0].get_allocator().resource();
    }

    // delete
    pool_resource(const pool_resource&) = delete;
    pool_resource& operator=(const pool_resource&) = delete;

  private:
    void* do_allocate(std::size_t bytes, std::size_t align) {
      auto remainder = _pools[0].capacity() - _pools[0].size();
      if (bytes > remainder) {
        std::swap(_pools[0], _pools[1]);
        pool_type tmp(policy::grow_up(_pools[1].capacity()) + std::max(bytes, align));
        std::swap(_pools[0], tmp);
      }

      auto old_size = (bytes > _pools[1].size()) ? 0uz : _pools[1].size();
      _pools[0].resize(old_size + bytes);

      return static_cast<void*>(_pools[0].data() + old_size);
    }

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t align) {
      std::swap(_pools[1], pool_type{});
    }

    bool do_is_equal(const memory_resource& other) const noexcept override {
      return this == &other;
    }

    /*
     * two pool_types: _pools[0]: current; _pools[1]: old; */
    std::vector<pool_type> _pools;
  };
} // namespace cxxjson::internal

#endif