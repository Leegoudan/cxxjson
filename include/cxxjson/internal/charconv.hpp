#pragma once
#ifndef CXXJSON_INTERNAL_CHARCONV_HPP
#define CXXJSON_INTERNAL_CHARCONV_HPP

#include <concepts>
#include <string>
#include <limits>

namespace cxxjson::internal {

    enum class chars_format {
    scientific = 1,
    fixed = 2,
    hex = 4,
    general = fixed | scientific
  };

  enum class errc {
    value_too_large
  };

  // 初等数值输出转换
  struct to_chars_result {
    char* ptr;
    errc ec;
    friend bool operator==(const to_chars_result&, const to_chars_result&) = default;
  };

  namespace detail {
      inline constexpr char _digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
        'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

      struct lut { char t, o; };
      inline static constexpr lut luts[100] = {
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


      inline to_chars_result itoa_more_1_less_10(char* first, char* last, unsigned int value) {
        if (value < 10) {
          *first = static_cast<char>(value) + '0';
          return {first + 1, errc{}};
        }
        if (value < 100) {
          *(lut*)&first[0] = luts[value];
          return {first + 2, errc{}};
        }
        
        if (value < 1000000) {
          if (value < 10000) {
            unsigned int up = value / 100;
            unsigned int down = value % 100;
            if (up >= 10) {
              *first++ = luts[up].t;
            }
            *first++ = luts[up].o;

            *(lut*)&first[0] = luts[down];
            return {first + 2, errc{}};
          } else {
            unsigned int up = value / 10000;
            unsigned int down = value % 10000;
            if (up >= 10) {
              *first++ = luts[up].t;
            }
            *first++ = luts[up].o;

            *(lut*)&first[0] = luts[down / 100];
            *(lut*)&first[2] = luts[down % 100];
            return {first + 4, errc{}};
          }
        } else {
          if (value < 100000000) {
            unsigned int up = value / 1000000;
            unsigned int down = value % 1000000;
            if (up >= 10) {
              *first++ = luts[up].t;
            }
            *first++ = luts[up].o;

            *(lut*)&first[0] = luts[down / 10000];
            *(lut*)&first[2] = luts[down % 10000 / 100];
            *(lut*)&first[4] = luts[down % 100];
            return {first + 6, errc{}};
          } else {
            unsigned int up = value / 100000000;
            unsigned int down = value % 100000000;

            if (up >= 10) {
              *first++ = luts[up].t;
            }
            *first++ = luts[up].o;

            *(lut*)&first[0] = luts[down / 1000000];
            *(lut*)&first[2] = luts[down % 1000000 / 10000];
            *(lut*)&first[4] = luts[down % 10000 / 100];
            *(lut*)&first[6] = luts[down % 100];
            return {first + 8, errc{}};
          }
        }
      }

    inline to_chars_result itoa_more_10_less_20(char* first, char* last, unsigned long long value) {
      unsigned long long up = value / 100000000;
      unsigned int down = value % 100000000;

      unsigned int dup = static_cast<unsigned int>(up);
      if (dup != up) {
        dup = up % 100000000;
        unsigned int sup = static_cast<unsigned int>(up / 100000000);
        unsigned int sup1 = sup / 100;
        unsigned int sup2 = sup % 100;
        if (sup1 >= 10)
          *first++ = luts[sup1].t;
        if (sup1 > 0)
          *first++ = luts[sup1].o;
        if (sup2 >= 10)
          *first++ = luts[sup2].t;
        *first++ = luts[sup2].o;
      }

      while (dup > 0) {
        if (dup < 10) {
          *first++ = static_cast<char>(dup) + '0'; break;
        }
        if (dup < 100) {
          *(lut*)&first[0] = luts[dup];
          first += 2; break;
        }

        if (dup < 1000000) {
          if (dup < 10000) {
            unsigned int dup1 = dup / 100;
            unsigned int dup2 = dup % 100;
            if (dup >= 10) {
              *first++ = luts[dup1].t;
            }
            *first++ = luts[dup1].o;

            *(lut*)&first[0] = luts[dup2];
            first += 2; break;
          } else {
            unsigned int dup1 = dup / 10000;
            unsigned int dup2 = dup % 10000;
            if (dup1 >= 10) {
              *first++ = luts[dup1].t;
            }
            *first++ = luts[dup1].o;

            *(lut*)&first[0] = luts[dup2 / 100];
            *(lut*)&first[2] = luts[dup2 % 100];
            first += 4; break;
          }
        } else {
          if (dup < 100000000) {
            unsigned int dup1 = dup / 1000000;
            unsigned int dup2 = dup % 1000000;
            if (dup1 >= 10) {
              *first++ = luts[dup1].t;
            }
            *first++ = luts[dup1].o;

            *(lut*)&first[0] = luts[dup2 / 10000];
            *(lut*)&first[2] = luts[dup2 % 10000 / 100];
            *(lut*)&first[4] = luts[dup2 % 100];
            first += 6; break;
          } else {
            unsigned int dup1 = dup / 100000000;
            unsigned int dup2 = dup % 100000000;

            if (dup1 >= 10) {
              *first++ = luts[dup1].t;
            }
            *first++ = luts[dup1].o;

            *(lut*)&first[0] = luts[dup2 / 1000000];
            *(lut*)&first[2] = luts[dup2 % 1000000 / 10000];
            *(lut*)&first[4] = luts[dup2 % 10000 / 100];
            *(lut*)&first[6] = luts[dup2 % 100];
            first += 8; break;
          }
        }
      }

      *(lut*)&first[0] = luts[down / 1000000];
      *(lut*)&first[2] = luts[down % 1000000 / 10000];
      *(lut*)&first[4] = luts[down % 10000 / 100];
      *(lut*)&first[6] = luts[down %  100];
      return {first + 8, errc{}};
    }
  }

  template<std::integral T>
  to_chars_result to_chars(char* first, char* last, T value, int base = 10) {
    static_assert(base >= 2 && base <= 36, "invalid base in to_chars()");
    using unsigned_t = make_unsigned_t<T>;
    unsigned_t unsigned_value = static_cast<unsigned_t>(value);

    if constexpr (std::is_signed_v<T>) {
        if (value < 0 && first == last) {
                return {last, errc::value_too_large};
            }

            *first++ = '-';
            unsigned_value = static_cast<unsigned_t>(-value);
    }
    
    static constexpr int digits = std::numeric_limits<T>::digits10 + 1;

    switch (base)
    {
    case 10:
      return (unsigned_value <= std::numeric_limits<unsigned int>::max() ? itoa_more_10_less_20(first, last, value) : itoa_more_10_less_20(first, last, value));
      break;
    case 2:
    case 4:
    case 8:
    case 16:

    case 3:

    case 5:
    case 6:
    case 7:
    case 9:
    
    default:
    do {
      *--last = _digits[unsigned_value % base];
      unsigned_value    = static_cast<unsigned_t>(unsigned_value / base);
    } while (unsigned_value != 0);
      break;
    }
  }
  to_chars_result to_chars(char* first, char* last, bool value, int base = 10) = delete;

  to_chars_result to_chars(char* first, char* last, float value);
  to_chars_result to_chars(char* first, char* last, double value);
  to_chars_result to_chars(char* first, char* last, long double value);
 
  to_chars_result to_chars(char* first, char* last, float value, chars_format fmt);
  to_chars_result to_chars(char* first, char* last, double value, chars_format fmt);
  to_chars_result to_chars(char* first, char* last, long double value, chars_format fmt);
 
  to_chars_result to_chars(char* first, char* last, float value, chars_format fmt, int precision);
  to_chars_result to_chars(char* first, char* last, double value, chars_format fmt, int precision);
  to_chars_result to_chars(char* first, char* last, long double value, chars_format fmt, int precision);


  // 初等数值输入转换
  struct from_chars_result {
    const char* ptr;
    errc ec;
    friend bool operator==(const from_chars_result&, const from_chars_result&) = default;
  };

  template<std::integral T>
  from_chars_result from_chars(const char* first, const char* last, const T& value, int base = 10);
 
  from_chars_result from_chars(const char* first, const char* last, float& value, chars_format fmt = chars_format::general);
  from_chars_result from_chars(const char* first, const char* last, double& value, chars_format fmt = chars_format::general);
  from_chars_result from_chars(const char* first, const char* last, long double& value, chars_format fmt = chars_format::general);
}

#endif