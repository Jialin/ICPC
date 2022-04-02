// !macro_gen
// ALL KMP_ALL
#pragma once

#include "common/macros.h"
#include "string/kmp/kmp_macros.h"

namespace str {

// TODO: unit test
template<typename T>
struct KMP {
#ifdef KMP_RESERVE // ^
  inline void reserve(int n) {
    _fails.reserve(n);
  }
#endif

  inline int calcNextPosition(int pos, const T& c) {
    if (pos == _n - 1) {
      pos = fails[pos];
    }
    for (; pos >= 0 && _pattern[pos + 1] != c; pos = fails[pos]) {}
    return pattern[pos + 1] == c ? pos + 1 : -1;
  }

#ifdef KMP_INIT // ^
  inline void init(int n, const T* pattern) {
    _n = n;
    _pattern = pattern;
    fails.resize(n);
    fails[0] = -1;
    FOR(i, 1, n) {
      fails[i] = calcNextPosition(fails[i], pattern[i]);
    }
  }
#endif

#ifdef KMP_MATCH_ALL // ^
  inline void matchAll(int m, const T* s, vector<int>& res) {
    int pos = -1;
    FOR(i, 0, m) {
      pos = calcNextPosition(pos, s[i]);
      if (pos == n - 1) {
        res.push_back(i - n + 1);
      }
    }
  }
#endif

  int _n;
  const T* _pattern;
  // fails[i]: represents the largest index j<i, where pattern[:j+1] is a suffix of pattern[:i+1]
  vector<int> _fails;
};

} // namespace str
