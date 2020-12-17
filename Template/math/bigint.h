#pragma once

#ifdef BIGINT_ALL
#define BIGINT_ADD
#define BIGINT_ADD_INLINE
#define BIGINT_ADD_INLINE_INT
#define BIGINT_ASSIGN
#define BIGINT_ASSIGN_CHAR_ARRAY
#define BIGINT_ASSIGN_INT
#define BIGINT_ASSIGN_STRING
#define BIGINT_CLEAN
#define BIGINT_CMP
#define BIGINT_CMP_INT
#define BIGINT_CONSTRUCT_EMPTY
#define BIGINT_CONSTRUCT_INT
#define BIGINT_DIGIT_COUNT
#define BIGINT_DIGIT_SUM
#define BIGINT_DIV_INLINE
#define BIGINT_DIV_INLINE_INT
#define BIGINT_DIV_MOD_INLINE_INT
#define BIGINT_GCD_INLINE
#define BIGINT_GT_INT
#define BIGINT_INIT_ADD
#define BIGINT_INIT_CAPACITY
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_INIT_INT
#define BIGINT_INIT_MUL
#define BIGINT_LT
#define BIGINT_MOD_DIV_INLINE
#define BIGINT_MOD_INLINE
#define BIGINT_MOD_INT
#define BIGINT_MUL_INLINE_INT
#define BIGINT_MUL_INT
#define BIGINT_PRINT
#define BIGINT_PRINT_CHAR_ARRAY
#define BIGINT_PRINT_QUICK
#define BIGINT_SUB_INLINE
#endif

#if defined(BIGINT_GCD_INLINE) || defined(BIGINT_LT)
#define BIGINT_CMP
#endif

#if defined(BIGINT_GCD_INLINE) || defined(BIGINT_GT_INT)
#define BIGINT_CMP_INT
#endif

#if defined(BIGINT_GCD_INLINE) || defined(BIGINT_DIV_INLINE_INT)
#define BIGINT_DIV_MOD_INLINE_INT
#endif

#ifdef BIGINT_MUL_INT
#define BIGINT_ASSIGN
#define BIGINT_MUL_INLINE_INT
#endif

#ifdef BIGINT_ADD
#define BIGINT_INIT_ADD
#endif

#ifdef BIGINT_INIT_ADD
#define BIGINT_ADD_INLINE
#define BIGINT_ASSIGN
#endif

#if defined(BIGINT_ASSIGN_INT) || defined(BIGINT_CONSTRUCT_INT)
#define BIGINT_INIT_INT
#endif

#if defined(BIGINT_DIV_INLINE) || defined(BIGINT_MOD_INLINE)
#define BIGINT_MOD_DIV_INLINE
#endif

#if defined(BIGINT_DIV_MOD_INLINE_INT) || defined(BIGINT_INIT_CHAR_ARRAY) ||   \
    defined(BIGINT_INIT_MUL) || defined(BIGINT_MOD_DIV_INLINE) ||              \
    defined(BIGINT_MUL_INLINE_INT) || defined(BIGINT_SUB_INLINE)
#define BIGINT_CLEAN
#endif

#if defined(BIGINT_ASSIGN_CHAR_ARRAY) || defined(BIGINT_ASSIGN_STRING)
#define BIGINT_INIT_CHAR_ARRAY
#endif

#if defined(BIGINT_ADD_INLINE) || defined(BIGINT_ADD_INLINE_INT) ||            \
    defined(BIGINT_CMP_INT) || defined(BIGINT_DIV_MOD_INLINE_INT) ||           \
    defined(BIGINT_INIT_INT) || defined(BIGINT_INIT_MUL) ||                    \
    defined(BIGINT_MOD_DIV_INLINE) || defined(BIGINT_MOD_INT) ||               \
    defined(BIGINT_MUL_INLINE_INT) || defined(BIGINT_SUB_INLINE)
#include "math/pow10.h"
#endif

#ifdef BIGINT_PRINT_QUICK
#include "io/write_int.h"
#endif

#include "debug/debug_basic.h"

using namespace std;

namespace math {

template<int GROUP = 9, typename BASE_SQR = int64_t>
struct BigInt {
#ifdef BIGINT_CONSTRUCT_EMPTY
  inline BigInt() {}
#endif

#ifdef BIGINT_CONSTRUCT_INT
  template<typename T>
  inline BigInt(T v) {
    initInt<T>(v);
  }
#endif

#ifdef BIGINT_INIT_CAPACITY
  inline void initCapacity(int capacity = -1) {
    if (capacity >= 0) {
      _vs.reserve((capacity + GROUP - 1) / GROUP);
    }
  }
#endif

#ifdef BIGINT_INIT_CHAR_ARRAY
  inline void initCharArray(const char* s, int size = -1) {
    _vs.clear();
    for (int i = (size >= 0 ? size : strlen(s)) - 1; i >= 0; i -= GROUP) {
      int v = 0;
      for (int j = min(i, GROUP - 1); j >= 0; --j) {
        v = v * 10 + s[i - j] - '0';
      }
      _vs.push_back(v);
    }
    clean();
  }
#endif

#ifdef BIGINT_INIT_INT
  template<typename T>
  inline void initInt(T v) {
    _vs.clear();
    for (; v; v /= POW10[GROUP]) {
      _vs.push_back(v % POW10[GROUP]);
    }
    if (_vs.empty()) {
      _vs.push_back(0);
    }
  }
#endif

#ifdef BIGINT_INIT_ADD
  inline void
  initAdd(const BigInt<GROUP, BASE_SQR>& x, const BigInt<GROUP, BASE_SQR>& y) {
    DEBUGF_NE(
        this,
        &x,
        "in a.initAdd(b,c), a and b should not reference to the same instance");
    DEBUGF_NE(
        this,
        &y,
        "in a.initAdd(b,c), a and c should not reference to the same instance");
    *this = x;
    *this += y;
  }
#endif

#ifdef BIGINT_INIT_MUL
  inline void
  initMul(const BigInt<GROUP, BASE_SQR>& x, const BigInt<GROUP, BASE_SQR>& y) {
    DEBUGF_NE(
        this,
        &x,
        "in a.initMul(b,c), a and b should not reference to the same instance");
    DEBUGF_NE(
        this,
        &y,
        "in a.initMul(b,c), a and c should not reference to the same instance");
    _vs.resize(x._vs.size() + y._vs.size());
    fill(_vs.begin(), _vs.end(), 0);
    for (int i = static_cast<int>(x._vs.size()) - 1; i >= 0; --i) {
      for (int j = 0, carry = 0; j < static_cast<int>(y._vs.size()) || carry;
           ++j) {
        BASE_SQR v = _vs[i + j] + carry;
        if (j < static_cast<int>(y._vs.size())) {
          v += static_cast<BASE_SQR>(x._vs[i]) * y._vs[j];
        }
        _vs[i + j] = static_cast<int>(v % POW10[GROUP]);
        carry = static_cast<int>(v / POW10[GROUP]);
      }
    }
    clean();
  }
#endif

#ifdef BIGINT_CLEAN
  inline void clean() {
    for (; _vs.size() > 1 && !_vs.back(); _vs.pop_back()) {}
  }
#endif

#ifdef BIGINT_ASSIGN
  inline void operator=(const BigInt<GROUP, BASE_SQR>& o) {
    _vs.clear();
    _vs.insert(_vs.begin(), o._vs.begin(), o._vs.end());
  }
#endif

#ifdef BIGINT_ASSIGN_CHAR_ARRAY
  inline void operator=(const char* s) {
    initCharArray(s);
  }
#endif

#ifdef BIGINT_ASSIGN_STRING
  inline void operator=(const string& o) {
    initCharArray(o.c_str(), o.size());
  }
#endif

#ifdef BIGINT_ASSIGN_INT
  template<typename T>
  inline void operator=(T o) {
    initInt<T>(o);
  }
#endif

#ifdef BIGINT_ADD
  inline BigInt<GROUP, BASE_SQR> operator+(const BigInt<GROUP, BASE_SQR>& o) {
    BigInt<GROUP, BASE_SQR> res;
    res.initAdd(*this, o);
    return res;
  }
#endif

#ifdef BIGINT_ADD_INLINE
  inline void operator+=(const BigInt<GROUP, BASE_SQR>& o) {
    bool carry = false;
    for (size_t i = 0; i < _vs.size() || i < o._vs.size() || carry; ++i) {
      if (i == _vs.size()) {
        _vs.push_back(0);
      }
      _vs[i] += carry + (i < o._vs.size() ? o._vs[i] : 0);
      carry = _vs[i] >= POW10[GROUP];
      if (carry) {
        _vs[i] -= POW10[GROUP];
      }
    }
  }
#endif

#ifdef BIGINT_ADD_INLINE_INT
  template<typename T>
  inline void operator+=(T v) {
    bool carry = false;
    for (size_t i = 0; i < _vs.size() || v || carry; ++i) {
      if (i == _vs.size()) {
        _vs.push_back(0);
      }
      if (v) {
        _vs[i] += v % POW10[GROUP];
        v /= POW10[GROUP];
      }
      if (carry) {
        ++_vs[i];
      }
      carry = _vs[i] >= POW10[GROUP];
      if (carry) {
        _vs[i] -= POW10[GROUP];
      }
    }
  }
#endif

#ifdef BIGINT_SUB_INLINE
  inline void operator-=(const BigInt<GROUP, BASE_SQR>& o) {
    DEBUGF_GE(
        this->cmp(o),
        0,
        "Should only subtract bigint that's not larger than o");
    bool carry = false;
    for (size_t i = 0; i < o._vs.size() || carry; ++i) {
      _vs[i] -= carry + (i < o._vs.size() ? o._vs[i] : 0);
      carry = _vs[i] < 0;
      if (carry) {
        _vs[i] += POW10[GROUP];
      }
    }
    clean();
  }
#endif

#ifdef BIGINT_MUL_INT
  inline BigInt<GROUP, BASE_SQR> operator*(BASE_SQR v) {
    BigInt<GROUP, BASE_SQR> res;
    res = *this;
    res *= v;
    return res;
  }
#endif

#ifdef BIGINT_MUL_INLINE_INT
  inline void operator*=(BASE_SQR v) {
    DEBUG_LT(v, POW10[GROUP]);
    int carry = 0;
    for (size_t i = 0; i < _vs.size() || carry; ++i) {
      if (i == _vs.size()) {
        _vs.push_back(0);
      }
      BASE_SQR cur = _vs[i] * v + carry;
      _vs[i] = static_cast<int>(cur % POW10[GROUP]);
      carry = static_cast<int>(cur / POW10[GROUP]);
    }
    clean();
  }
#endif

#ifdef BIGINT_DIV_INLINE
  inline void operator/=(const BigInt<GROUP, BASE_SQR>& o) {
    BigInt<GROUP, BASE_SQR> divRes;
    modDivInline(o, divRes);
    *this = move(divRes);
  }
#endif

#ifdef BIGINT_DIV_INLINE_INT
  inline void operator/=(BASE_SQR v) {
    divInt(v);
  }
#endif

#ifdef BIGINT_MOD_INLINE
  inline void operator%=(const BigInt<GROUP, BASE_SQR>& o) {
    BigInt<GROUP, BASE_SQR> divRes;
    modDivInline(o, divRes);
  }
#endif

#ifdef BIGINT_MOD_INT
  inline BASE_SQR operator%(BASE_SQR v) {
    DEBUG_GT(v, 0);
    DEBUG_LE(v - 1, numeric_limits<BASE_SQR>::max() / POW10[GROUP]);
    BASE_SQR mod = 0;
    for (int i = static_cast<int>(_vs.size()) - 1; i >= 0; --i) {
      mod = (_vs[i] + mod * POW10[GROUP]) % v;
    }
    return mod;
  }
#endif

#ifdef BIGINT_LT
  inline bool operator<(const BigInt<GROUP, BASE_SQR>& o) const {
    return cmp(o) < 0;
  }
#endif

#ifdef BIGINT_GT_INT
  template<typename T>
  inline bool operator>(T v) const {
    return cmp<T>(v) > 0;
  }
#endif

#ifdef BIGINT_MOD_DIV_INLINE
  inline void modDivInline(
      const BigInt<GROUP, BASE_SQR>& o, BigInt<GROUP, BASE_SQR>& divRes) {
    divRes._vs.resize(max(
        static_cast<int>(_vs.size()) - static_cast<int>(o._vs.size()) + 1, 1));
    fill(divRes._vs.begin(), divRes._vs.end(), 0);
    for (int i = static_cast<int>(divRes._vs.size()) - 1; i >= 0; --i) {
      int res = 0;
      for (int lower = 1, upper = POW10[GROUP] - 1; lower <= upper;) {
        int medium = (lower + upper) >> 1;
        if (isLessThanShiftCmp(o, medium, i)) {
          upper = medium - 1;
        } else {
          res = medium;
          lower = medium + 1;
        }
      }
      divRes._vs[i] = res;
      shiftSubInline(o, res, i);
    }
    clean();
    divRes.clean();
  }

  inline void
  shiftSubInline(const BigInt<GROUP, BASE_SQR>& o, BASE_SQR mul, int shift) {
    BASE_SQR carry = 0;
    for (size_t i = 0, j = shift; i < o._vs.size(); ++i, ++j) {
      BASE_SQR delta = carry + o._vs[i] * mul;
      if (_vs[j] >= delta) {
        _vs[j] -= delta;
        carry = 0;
      } else {
        carry = (delta - _vs[j] + POW10[GROUP] - 1) / POW10[GROUP];
        _vs[j] -= delta - carry * POW10[GROUP];
      }
    }
    for (size_t i = o._vs.size() + shift; i < _vs.size(); ++i) {
      if (_vs[i] >= carry) {
        _vs[i] -= carry;
        break;
      }
      BASE_SQR delta = carry;
      carry = (carry - _vs[i] + POW10[GROUP] + 1) / POW10[GROUP];
      _vs[i] -= delta - carry * POW10[GROUP];
    }
    clean();
  }

  inline bool isLessThanShiftCmp(
      const BigInt<GROUP, BASE_SQR>& o, BASE_SQR mul, int shift) {
    if (mul && _vs.size() < o._vs.size() + shift) {
      return true;
    }
    BASE_SQR carry = 0;
    for (int i = static_cast<int>(_vs.size()) - 1, j = i - shift; i >= 0;
         --i, --j) {
      carry = carry * POW10[GROUP] + _vs[i];
      if (0 <= j && j < o._vs.size()) {
        if (carry < mul * o._vs[j]) {
          return true;
        }
        carry -= mul * o._vs[j];
      }
      if (carry > POW10[GROUP] << 1) {
        return false;
      }
    }
    return false;
  }
#endif

#ifdef BIGINT_DIV_MOD_INLINE_INT
  inline BASE_SQR divModInlineInt(BASE_SQR v) {
    DEBUG_LE(v - 1, numeric_limits<BASE_SQR>::max() / POW10[GROUP]);
    BASE_SQR mod = 0;
    for (int i = static_cast<int>(_vs.size()) - 1; i >= 0; --i) {
      BASE_SQR cur = _vs[i] + mod * POW10[GROUP];
      _vs[i] = cur / v;
      mod = cur % v;
    }
    clean();
    return mod;
  }
#endif

#ifdef BIGINT_CMP
  inline int cmp(const BigInt<GROUP, BASE_SQR>& o) const {
    if (_vs.size() != o._vs.size()) {
      return _vs.size() < o._vs.size() ? -1 : 1;
    }
    for (int i = static_cast<int>(_vs.size()) - 1; i >= 0; --i) {
      if (_vs[i] != o._vs[i]) {
        return _vs[i] < o._vs[i] ? -1 : 1;
      }
    }
    return 0;
  }
#endif

#ifdef BIGINT_CMP_INT
  template<typename T>
  inline int cmp(T o, size_t idx = 0) const {
    if (!o) {
      if (idx + 1 < _vs.size()) {
        return 1;
      }
      int v = idx < _vs.size() ? _vs[idx] : 0;
      if (v != o) {
        return v < o ? -1 : 1;
      }
      return 0;
    }
    if (idx >= _vs.size()) {
      return -1;
    }
    int res = cmp(o / POW10[GROUP], idx + 1);
    if (res) {
      return res;
    }
    int mod = o % POW10[GROUP];
    if (_vs[idx] != mod) {
      return _vs[idx] < mod ? -1 : 1;
    }
    return 0;
  }
#endif

#ifdef BIGINT_GCD_INLINE
  inline void gcdInline(BigInt<GROUP, BASE_SQR>& o) {
    if (cmp(o) < 0) {
      swap(*this, o);
    }
    BigInt<GROUP, BASE_SQR> divRes;
    while (o.cmp(0) > 0) {
      modDivInline(o, divRes);
      swap(*this, o);
    }
  }
#endif

#ifdef BIGINT_DIGIT_COUNT
  inline int digitCount() const {
    int res = (static_cast<int>(_vs.size()) - 1) * GROUP + 1;
    for (int v = _vs.back() / 10; v; v /= 10, ++res) {}
    return res;
  }
#endif

#ifdef BIGINT_DIGIT_SUM
  inline int digitSum() const {
    int res = 0;
    for (int v : _vs) {
      for (; v; v /= 10) {
        res += v % 10;
      }
    }
    return res;
  }
#endif

#ifdef BIGINT_PRINT
  inline void print() const {
    int idx = static_cast<int>(_vs.size()) - 1;
    printf("%d", _vs[idx]);
    for (int i = idx - 1; i >= 0; --i) {
      printf("%0*d", GROUP, _vs[i]);
    }
  }
#endif

#ifdef BIGINT_PRINT_QUICK
  inline void printQuick() const {
    int idx = static_cast<int>(_vs.size()) - 1;
    io::writeInt(_vs[idx]);
    for (int i = idx - 1; i >= 0; --i) {
      io::writeInt(_vs[i], GROUP);
    }
  }
#endif

#ifdef BIGINT_PRINT_CHAR_ARRAY
  inline void printCharArray(char* res) const {
    int idx = static_cast<int>(_vs.size()) - 1;
    res += _printInt(_vs[idx], res);
    for (int i = idx - 1; i >= 0; --i) {
      res += _printInt(_vs[i], res, GROUP);
    }
    *res = '\0';
  }

  inline int _printInt(int x, char* res, int padding = 0) const {
    static char s[10];
    int n = 0;
    for (; x || !n; x /= 10) {
      s[n++] = '0' + x % 10;
    }
    for (int i = n; i < padding; ++i) {
      *(res++) = '0';
    }
    for (int i = n - 1; i >= 0; --i) {
      *(res++) = s[i];
    }
    return max(padding, n);
  }
#endif

  vector<int> _vs;
};

} // namespace math
