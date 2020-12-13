#pragma once

#ifdef BIGINT_ALL
#define BIGINT_ADD_INLINE
#define BIGINT_ASSIGN
#define BIGINT_ASSIGN_CHAR_ARRAY
#define BIGINT_ASSIGN_INT
#define BIGINT_ASSIGN_STRING
#define BIGINT_CLEAN
#define BIGINT_COMPARE
#define BIGINT_COMPARE_INT
#define BIGINT_CONSTRUCT_EMPTY
#define BIGINT_CONSTRUCT_INT
#define BIGINT_INIT_CAPACITY
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_INIT_INT
#define BIGINT_LENGTH
#endif

#if defined(BIGINT_ADD_INLINE) || defined(BIGINT_ASSIGN_INT) ||                \
    defined(BIGINT_COMPARE_INT) || defined(BIGINT_INIT_INT) ||                 \
    defined(BIGINT_LENGTH)
#include "math/pow10.h"
#endif

using namespace std;

namespace math {

template<int GROUP = 4>
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

#if defined(BIGINT_ASSIGN_CHAR_ARRAY) || defined(BIGINT_ASSIGN_STRING) ||      \
    defined(BIGINT_INIT_CHAR_ARRAY)
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

#if defined(BIGINT_ASSIGN_INT) || defined(BIGINT_CONSTRUCT_INT) ||             \
    defined(BIGINT_INIT_INT)
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

#if defined(BIGINT_CLEAN) || defined(BIGINT_INIT_CHAR_ARRAY)
  inline void clean() {
    for (; _vs.size() > 1 && !_vs.back(); _vs.pop_back()) {}
  }
#endif

#ifdef BIGINT_ASSIGN
  inline void operator=(const BigInt<GROUP>& o) {
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

#ifdef BIGINT_ADD_INLINE
  inline void operator+=(const BigInt<GROUP>& o) {
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

#ifdef BIGINT_COMPARE
  inline int cmp(const BigInt<GROUP>& o) const {
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

  vector<int> _vs;
};

} // namespace math
