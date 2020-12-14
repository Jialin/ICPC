#pragma once

#ifdef BIGINT_ALL
#define BIGINT_ADD_INLINE
#define BIGINT_ADD_INLINE_INT
#define BIGINT_ASSIGN
#define BIGINT_ASSIGN_CHAR_ARRAY
#define BIGINT_ASSIGN_INT
#define BIGINT_ASSIGN_STRING
#define BIGINT_CLEAN
#define BIGINT_COMPARE
#define BIGINT_COMPARE_INT
#define BIGINT_CONSTRUCT_EMPTY
#define BIGINT_CONSTRUCT_INT
#define BIGINT_INIT_ADD
#define BIGINT_INIT_CAPACITY
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_INIT_INT
#define BIGINT_INIT_MUL
#define BIGINT_LENGTH
#define BIGINT_MUL_INLINE_INT
#define BIGINT_PRINT
#define BIGINT_PRINT_CHAR_ARRAY
#define BIGINT_PRINT_QUICK
#endif

#if defined(BIGINT_ADD_INLINE) || defined(BIGINT_ADD_INLINE_INT) ||            \
    defined(BIGINT_ASSIGN_INT) || defined(BIGINT_COMPARE_INT) ||               \
    defined(BIGINT_INIT_INT) || defined(BIGINT_INIT_MUL) ||                    \
    defined(BIGINT_LENGTH) || defined(BIGINT_MUL_INLINE_INT)
#include "math/pow10.h"
#endif
#ifdef BIGINT_PRINT_QUICK
#include "io/write_int.h"
#endif

#include "debug/debug_basic.h"

using namespace std;

namespace math {

template<int GROUP = 9, typename BASE_SQR = uint64_t>
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

#if defined(BIGINT_INIT_CHAR_ARRAY) || defined(BIGINT_ASSIGN_CHAR_ARRAY) ||    \
    defined(BIGINT_ASSIGN_STRING) || defined(BIGINT_MUL_INLINE_INT)
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

#if defined(BIGINT_INIT_INT) || defined(BIGINT_ASSIGN_INT) ||                  \
    defined(BIGINT_CONSTRUCT_INT)
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
    DEBUG_TRUE(
        this != &x,
        "in `a.initMul(b,c)`, a and b should not reference to the same "
        "instance",
        nullptr);
    DEBUG_TRUE(
        this != &y,
        "in `a.initMul(b,c)`, a and b should not reference to the same "
        "instance",
        nullptr);
    *this = x;
    *this += y;
  }
#endif

#ifdef BIGINT_INIT_MUL
  inline void
  initMul(const BigInt<GROUP, BASE_SQR>& x, const BigInt<GROUP, BASE_SQR>& y) {
    DEBUG_TRUE(
        this != &x,
        "in `a.initMul(b,c)`, a and b should not reference to the same "
        "instance",
        nullptr);
    DEBUG_TRUE(
        this != &y,
        "in `a.initMul(b,c)`, a and b should not reference to the same "
        "instance",
        nullptr);
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

#if defined(BIGINT_CLEAN) || defined(BIGINT_INIT_CHAR_ARRAY) ||                \
    defined(BIGINT_INIT_MUL)
  inline void clean() {
    for (; _vs.size() > 1 && !_vs.back(); _vs.pop_back()) {}
  }
#endif

#if defined(BIGINT_ASSIGN) || defined(BIGINT_INIT_ADD)
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

#if defined(BIGINT_ADD_INLINE) || defined(BIGINT_INIT_ADD)
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

#ifdef BIGINT_MUL_INLINE_INT
  inline void operator*=(BASE_SQR v) {
    DEBUG_TRUE(v < POW10[GROUP], "v(%d) should be less than 10^%d.", v, GROUP);
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

#ifdef BIGINT_COMPARE
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

#ifdef BIGINT_COMPARE_INT
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
    int remainder = o % POW10[GROUP];
    if (_vs[idx] != remainder) {
      return _vs[idx] < remainder ? -1 : 1;
    }
    return 0;
  }
#endif

#ifdef BIGINT_LENGTH
  inline int length() const {
    int res = (static_cast<int>(_vs.size()) - 1) * GROUP + 1;
    for (int v = _vs.back() / 10; v; v /= 10, ++res) {}
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
