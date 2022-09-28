#pragma once
#ifndef CXXJSON_INTERNAL_ITOA_HPP
#define CXXJSON_INTERNAL_ITOA_HPP

#include <concepts>
#include <limits>

namespace cxxjson::internal::detail {
  struct lut { char t, o; };
  inline static const lut luts[100] = {
    {'0','0'},{'0','1'},{'0','2'},{'0','3'},{'0','4'},{'0','5'},{'0','6'},{'0','7'},{'0','8'},{'0','9'},
    {'1','0'},{'1','1'},{'1','2'},{'1','3'},{'1','4'},{'1','5'},{'1','6'},{'1','7'},{'1','8'},{'1','9'},
    {'2','0'},{'2','1'},{'2','2'},{'2','3'},{'2','4'},{'2','5'},{'2','6'},{'2','7'},{'2','8'},{'2','9'},
    {'3','0'},{'3','1'},{'3','2'},{'3','3'},{'3','4'},{'3','5'},{'3','6'},{'3','7'},{'3','8'},{'3','9'},
    {'4','0'},{'4','1'},{'4','2'},{'4','3'},{'4','4'},{'4','5'},{'4','6'},{'4','7'},{'4','8'},{'4','9'},
    {'5','0'},{'5','1'},{'5','2'},{'5','3'},{'5','4'},{'5','5'},{'5','6'},{'5','7'},{'5','8'},{'5','9'},
    {'6','0'},{'6','1'},{'6','2'},{'6','3'},{'6','4'},{'6','5'},{'6','6'},{'6','7'},{'6','8'},{'6','9'},
    {'7','0'},{'7','1'},{'7','2'},{'7','3'},{'7','4'},{'7','5'},{'7','6'},{'7','7'},{'7','8'},{'7','9'},
    {'8','0'},{'8','1'},{'8','2'},{'8','3'},{'8','4'},{'8','5'},{'8','6'},{'8','7'},{'8','8'},{'8','9'},
    {'9','0'},{'9','1'},{'9','2'},{'9','3'},{'9','4'},{'9','5'},{'9','6'},{'9','7'},{'9','8'},{'9','9'}
  };

  template<typename Iter> requires (requires(Iter it){*it = '0';})
  inline Iter itoa_more_1_less_10(unsigned int src, Iter begin, Iter end) {
    if (src < 10) {
      *begin = static_cast<char>(src) + '0';
      return begin + 1;
    }
    if (src < 100) {
      *(lut*)&begin[0] = luts[src];
      return begin + 2;
    }
    
    if (src < 1000000) {
      if (src < 10000) {
        unsigned int up = src / 100;
        unsigned int down = src % 100;
        if (up >= 10) {
          *begin++ = luts[up].t;
        }
        *begin++ = luts[up].o;

        *(lut*)&begin[0] = luts[down];
        return begin + 2;
      } else {
        unsigned int up = src / 10000;
        unsigned int down = src % 10000;
        if (up >= 10) {
          *begin++ = luts[up].t;
        }
        *begin++ = luts[up].o;

        *(lut*)&begin[0] = luts[down / 100];
        *(lut*)&begin[2] = luts[down % 100];
        return begin + 4;
      }
    } else {
      if (src < 100000000) {
        unsigned int up = src / 1000000;
        unsigned int down = src % 1000000;
        if (up >= 10) {
          *begin++ = luts[up].t;
        }
        *begin++ = luts[up].o;

        *(lut*)&begin[0] = luts[down / 10000];
        *(lut*)&begin[2] = luts[down % 10000 / 100];
        *(lut*)&begin[4] = luts[down % 100];
        return begin + 6;
      } else {
        unsigned int up = src / 100000000;
        unsigned int down = src % 100000000;

        if (up >= 10) {
          *begin++ = luts[up].t;
        }
        *begin++ = luts[up].o;

        *(lut*)&begin[0] = luts[down / 1000000];
        *(lut*)&begin[2] = luts[down % 1000000 / 10000];
        *(lut*)&begin[4] = luts[down % 10000 / 100];
        *(lut*)&begin[6] = luts[down % 100];
        return begin + 8;
      }
    }
  }

  template<typename Iter> requires (requires(Iter it){*it = '0';})
  inline Iter itoa_more_10_less_20(unsigned long long src, Iter begin, Iter end) {
    unsigned long long up = src / 100000000;
    unsigned int down = src % 100000000;

    unsigned int dup = static_cast<unsigned int>(up);
    if (dup != up) {
      dup = up % 100000000;
      unsigned int sup = static_cast<unsigned int>(up / 100000000);
      unsigned int sup1 = sup / 100;
      unsigned int sup2 = sup % 100;
      if (sup1 >= 10)
        *begin++ = luts[sup1].t;
      if (sup1 > 0)
        *begin++ = luts[sup1].o;
      if (sup2 >= 10)
        *begin++ = luts[sup2].t;
      *begin++ = luts[sup2].o;
    }

    while (dup > 0) {
      if (dup < 10) {
        *begin++ = static_cast<char>(dup) + '0'; break;
      }
      if (dup < 100) {
        *(lut*)&begin[0] = luts[dup];
        begin += 2; break;
      }

      if (dup < 1000000) {
        if (dup < 10000) {
          unsigned int dup1 = dup / 100;
          unsigned int dup2 = dup % 100;
          if (dup >= 10) {
            *begin++ = luts[dup1].t;
          }
          *begin++ = luts[dup1].o;

          *(lut*)&begin[0] = luts[dup2];
          begin += 2; break;
        } else {
          unsigned int dup1 = dup / 10000;
          unsigned int dup2 = dup % 10000;
          if (dup1 >= 10) {
            *begin++ = luts[dup1].t;
          }
          *begin++ = luts[dup1].o;

          *(lut*)&begin[0] = luts[dup2 / 100];
          *(lut*)&begin[2] = luts[dup2 % 100];
          begin += 4; break;
        }
      } else {
        if (dup < 100000000) {
          unsigned int dup1 = dup / 1000000;
          unsigned int dup2 = dup % 1000000;
          if (dup1 >= 10) {
            *begin++ = luts[dup1].t;
          }
          *begin++ = luts[dup1].o;

          *(lut*)&begin[0] = luts[dup2 / 10000];
          *(lut*)&begin[2] = luts[dup2 % 10000 / 100];
          *(lut*)&begin[4] = luts[dup2 % 100];
          begin += 6; break;
        } else {
          unsigned int dup1 = dup / 100000000;
          unsigned int dup2 = dup % 100000000;

          if (dup1 >= 10) {
            *begin++ = luts[dup1].t;
          }
          *begin++ = luts[dup1].o;

          *(lut*)&begin[0] = luts[dup2 / 1000000];
          *(lut*)&begin[2] = luts[dup2 % 1000000 / 10000];
          *(lut*)&begin[4] = luts[dup2 % 10000 / 100];
          *(lut*)&begin[6] = luts[dup2 % 100];
          begin += 8; break;
        }
      }
    }

    *(lut*)&begin[0] = luts[down / 1000000];
    *(lut*)&begin[2] = luts[down % 1000000 / 10000];
    *(lut*)&begin[4] = luts[down % 10000 / 100];
    *(lut*)&begin[6] = luts[down %  100];
    return begin + 8;
  }

  template<std::integral Src, typename Iter>
  Iter itoa(Src src, Iter begin, Iter end) {
    if (begin == end) return end;
    if (src < 0) {
      *begin++ = '-';
      if (src < std::numeric_limits<int>::min()) {
        unsigned long long u = - static_cast<unsigned long long>(src);
        return itoa_more_10_less_20(u, begin, end);
      } else {
        unsigned int u = - static_cast<unsigned int>(src);
        return itoa_more_1_less_10(u, begin, end);
      }
    } else {
      if (src > std::numeric_limits<unsigned int>::max()) {
        unsigned long long u = src;
        return itoa_more_10_less_20(u, begin, end);
      } else {
        unsigned int u = src;
        return itoa_more_1_less_10(u, begin, end);
      }
    }
  }
}

#endif