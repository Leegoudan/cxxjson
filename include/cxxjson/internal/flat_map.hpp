#pragma once
#ifndef CXXJSON_INTERNAL_FLAT_MAP_HPP
#define CXXJSON_INTERNAL_FLAT_MAP_HPP

#include <compare>
#include <initializer_list>
#include <vector>
//#include <ranges>

/*
 * p0429r6
 * https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0429r6.pdf */

namespace cxxjson::internal {
  // [flat.map], class template flat_­map
  template <class Key, class T, class Compare = std::less<Key>, class KeyContainer = std::vector<Key>, class MappedContainer = std::vector<T>>
  class flat_map;

  struct sorted_unique_t {
    explicit sorted_unique_t() = default;
  };
  inline constexpr sorted_unique_t sorted_unique{};

  template <class _Ty, class _Alloc>
  struct uses_allocator : std::uses_allocator<Container, Alloc>::type {};

  template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Allocator>
  struct uses_allocator<flat_map<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>;

  template <class Key, class T, class Compare = std::less<Key>, class KeyContainer = std::vector<Key>, class MappedContainer = std::vector<T>>
  class flat_map {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<key_type, mapped_type>;
    using key_compare = Compare;
    using reference = std::pair<const key_type&, mapped_type&>;
    using const_reference = std::pair<const key_type&, const mapped_type&>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator = implementation - defined;       // see [container.requirements]
    using const_iterator = implementation - defined; // see [container.requirements]
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using key_container_type = KeyContainer;
    using mapped_container_type = MappedContainer;

    class value_compare {
    private:
      key_compare comp;                         // exposition only
      value_compare(key_compare c) : comp(c) {} // exposition only
    public:
      bool operator()(const_reference x, const_reference y) const { return comp(x.first, y.first); }
    };

    struct containers {
      key_container_type keys;
      mapped_container_type values;
    };
    // [flat.map.cons], construct/copy/destroy
    flat_map() : flat_map(key_compare()) {}

    flat_map(key_container_type key_cont, mapped_container_type mapped_cont);
    template <class Allocator>
    flat_map(const key_container_type& key_cont, const mapped_container_type& mapped_cont, const Allocator& a);

    flat_map(sorted_unique_t, key_container_type key_cont, mapped_container_type mapped_cont);
    template <class Allocator>
    flat_map(sorted_unique_t, const key_container_type& key_cont, const mapped_container_type& mapped_cont, const Allocator& a);

    explicit flat_map(const key_compare& comp) : c(), compare(comp) {}
    template <class Allocator>
    flat_map(const key_compare& comp, const Allocator& a);
    template <class Allocator>
    explicit flat_map(const Allocator& a);

    template <class InputIterator>
    flat_map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : c(), compare(comp) {
      insert(first, last);
    }
    template <class InputIterator, class Allocator>
    flat_map(InputIterator first, InputIterator last, const key_compare& comp, const Allocator& a);
    template <class InputIterator, class Allocator>
    flat_map(InputIterator first, InputIterator last, const Allocator& a);

    template <container - compatible - range<value_type> R>
    flat_map(from_range_t fr, R&& rg) : flat_map(fr, std::forward<R>(rg), key_compare()) {}
    template <container - compatible - range<value_type> R, class Allocator>
    flat_map(from_range_t, R&& rg, const Allocator& a);
    template <container - compatible - range<value_type> R>
    flat_map(from_range_t, R&& rg, const key_compare& comp) : flat_map(comp) {
      insert_range(std::forward<R>(rg));
    }
    template <container - compatible - range<value_type> R, class Allocator>
    flat_map(from_range_t, R&& rg, const key_compare& comp, const Allocator& a);

    template <class InputIterator>
    flat_map(sorted_unique_t s, InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : c(), compare(comp) {
      insert(s, first, last);
    }
    template <class InputIterator, class Allocator>
    flat_map(sorted_unique_t, InputIterator first, InputIterator last, const key_compare& comp, const Allocator& a);
    template <class InputIterator, class Allocator>
    flat_map(sorted_unique_t, InputIterator first, InputIterator last, const Allocator& a);

    flat_map(std::initializer_list<value_type> il, const key_compare& comp = key_compare()) : flat_map(il.begin(), il.end(), comp) {}
    template <class Allocator>
    flat_map(std::initializer_list<value_type> il, const key_compare& comp, const Allocator& a);
    template <class Allocator>
    flat_map(std::initializer_list<value_type> il, const Allocator& a);

    flat_map(sorted_unique_t s, std::initializer_list<value_type> il, const key_compare& comp = key_compare()) : flat_map(s, il.begin(), il.end(), comp) {}
    template <class Allocator>
    flat_map(sorted_unique_t, std::initializer_list<value_type> il, const key_compare& comp, const Allocator& a);
    template <class Allocator>
    flat_map(sorted_unique_t, std::initializer_list<value_type> il, const Allocator& a);

    flat_map& operator=(std::initializer_list<value_type> il);

    // iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // [flat.map.capacity], capacity
    [[nodiscard]] bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    // [flat.map.access], element access
    mapped_type& operator[](const key_type& x);
    mapped_type& operator[](key_type&& x);
    template <class K>
    mapped_type& operator[](K&& x);
    mapped_type& at(const key_type& x);
    const mapped_type& at(const key_type& x) const;
    template <class K>
    mapped_type& at(const K& x);
    template <class K>
    const mapped_type& at(const K& x) const;

    // [flat.map.modifiers], modifiers
    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
    iterator emplace_hint(const_iterator position, Args&&... args);

    std::pair<iterator, bool> insert(const value_type& x) { return emplace(x); }
    std::pair<iterator, bool> insert(value_type&& x) { return emplace(std::move(x)); }
    iterator insert(const_iterator position, const value_type& x) { return emplace_hint(position, x); }
    iterator insert(const_iterator position, value_type&& x) { return emplace_hint(position, std::move(x)); }

    template <class P>
    std::pair<iterator, bool> insert(P&& x);
    template <class P>
    iterator insert(const_iterator position, P&&);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);
    template <class InputIterator>
    void insert(sorted_unique_t, InputIterator first, InputIterator last);
    template <container - compatible - range<value_type> R>
    void insert_range(R&& rg);

    void insert(std::initializer_list<value_type> il) { insert(il.begin(), il.end()); }
    void insert(sorted_unique_t s, std::initializer_list<value_type> il) { insert(s, il.begin(), il.end()); }

    containers extract() &&;
    void replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont);

    template <class... Args>
    std::pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
    template <class... Args>
    std::pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);
    template <class K, class... Args>
    std::pair<iterator, bool> try_emplace(K&& k, Args&&... args);
    template <class... Args>
    iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
    template <class... Args>
    iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);
    template <class K, class... Args>
    iterator try_emplace(const_iterator hint, K&& k, Args&&... args);
    template <class M>
    std::pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
    template <class M>
    std::pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
    template <class K, class M>
    std::pair<iterator, bool> insert_or_assign(K&& k, M&& obj);
    template <class M>
    iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
    template <class M>
    iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);
    template <class K, class M>
    iterator insert_or_assign(const_iterator hint, K&& k, M&& obj);

    iterator erase(iterator position);
    iterator erase(const_iterator position);
    size_type erase(const key_type& x);
    template <class K>
    size_type erase(K&& x);
    iterator erase(const_iterator first, const_iterator last);

    void swap(flat_map& y) noexcept;
    void clear() noexcept;

    // observers
    key_compare key_comp() const;
    value_compare value_comp() const;

    const key_container_type& keys() const noexcept { return c.keys; }
    const mapped_container_type& values() const noexcept { return c.values; }

    // map operations
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
    template <class K>
    iterator find(const K& x);
    template <class K>
    const_iterator find(const K& x) const;

    size_type count(const key_type& x) const;
    template <class K>
    size_type count(const K& x) const;

    bool contains(const key_type& x) const;
    template <class K>
    bool contains(const K& x) const;

    iterator lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
    template <class K>
    iterator lower_bound(const K& x);
    template <class K>
    const_iterator lower_bound(const K& x) const;

    iterator upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
    template <class K>
    iterator upper_bound(const K& x);
    template <class K>
    const_iterator upper_bound(const K& x) const;

    std::pair<iterator, iterator> equal_range(const key_type& x);
    std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
    template <class K>
    std::pair<iterator, iterator> equal_range(const K& x);
    template <class K>
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const;

    friend bool operator==(const flat_map& x, const flat_map& y);

    friend synth - three - way - result<value_type> operator<=>(const flat_map& x, const flat_map& y);

    friend void swap(flat_map& x, flat_map& y) noexcept { x.swap(y); }

  private:
    containers c;        // exposition only
    key_compare compare; // exposition only

    struct key_equiv { // exposition only
      key_equiv(key_compare c) : comp(c) {}
      bool operator()(const_reference x, const_reference y) const { return !comp(x.first, y.first) && !comp(y.first, x.first); }
      key_compare comp;
    };
  };

  template <class KeyContainer, class MappedContainer>
  flat_map(KeyContainer, MappedContainer) -> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type,
                                                      std::less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;

  template <class KeyContainer, class MappedContainer, class Allocator>
  flat_map(KeyContainer, MappedContainer, Allocator) -> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type,
                                                                 std::less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;

  template <class KeyContainer, class MappedContainer>
  flat_map(sorted_unique_t, KeyContainer, MappedContainer) -> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type,
                                                                       std::less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;

  template <class KeyContainer, class MappedContainer, class Allocator>
  flat_map(sorted_unique_t, KeyContainer, MappedContainer, Allocator)
      -> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, std::less<typename KeyContainer::value_type>, KeyContainer,
                  MappedContainer>;

  template <class InputIterator, class Compare = std::less<iter - key - type<InputIterator>>>
  flat_map(InputIterator, InputIterator, Compare = Compare())
      -> flat_map<iter - key - type<InputIterator>, iter - mapped - type<InputIterator>, Compare>;

  template <class InputIterator, class Compare = std::less<iter - key - type<InputIterator>>>
  flat_map(sorted_unique_t, InputIterator, InputIterator, Compare = Compare())
      -> flat_map<iter - key - type<InputIterator>, iter - mapped - type<InputIterator>, Compare>;

  template <std::ranges::input_range R, class Compare = std::less<range - key - type<R>>, class Allocator>
  flat_map(from_range_t, R&&, Compare = Compare(), Allocator = Allocator()) -> flat_map<range - key - type<R>, range - mapped - type<R>, Compare>;

  template <std::ranges::input_range R, class Allocator>
  flat_map(from_range_t, R&&, Allocator) -> flat_map<range - key - type<R>, range - mapped - type<R>>;

  template <class Key, class T, class Compare = std::less<Key>>
  flat_map(std::initializer_list<std::pair<Key, T>>, Compare = Compare()) -> flat_map<Key, T, Compare>;

  template <class Key, class T, class Compare = std::less<Key>>
  flat_map(sorted_unique_t, std::initializer_list<std::pair<Key, T>>, Compare = Compare()) -> flat_map<Key, T, Compare>;

  template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Allocator>
  struct uses_allocator<flat_map<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>
      : bool_constant<std::uses_allocator_v<KeyContainer, Allocator> && std::uses_allocator_v<MappedContainer, Allocator>> {};
};

// [flat.map.erasure], erasure for flat_­map
template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Predicate>
typename flat_map<Key, T, Compare, KeyContainer, MappedContainer>::size_type erase_if(flat_map<Key, T, Compare, KeyContainer, MappedContainer>& c,
                                                                                      Predicate pred);

// [flat.multimap], class template flat_­multimap
template <class Key, class T, class Compare = std::less<Key>, class KeyContainer = std::vector<Key>, class MappedContainer = std::vector<T>>
class flat_multimap;

struct sorted_equivalent_t {
  explicit sorted_equivalent_t() = default;
};
inline constexpr sorted_equivalent_t sorted_equivalent{};

template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Allocator>
struct uses_allocator<flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>;

// [flat.multimap.erasure], erasure for flat_­multimap
template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Predicate>
typename flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>::size_type
erase_if(flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred);
} // namespace cxxjson::internal

#endif