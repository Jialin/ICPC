// !macro_gen
// ALL Z_FUNCTION_ALL
#pragma once

#include "common/macros.h"
#include "string/kmp/z_function_macros.h"

using namespace std;

namespace str {

template<typename T>
struct ZFunction {
#ifdef Z_FUNCTION_RESERVE // ^
  inline void reserve(int n) {
    _prefixs.reserve(n);
  }
#endif

#ifdef Z_FUNCTION_INIT // ^
  inline void init(int n, const T* pattern) {
    _prefixs.resize(n);
    _prefixs[0] = n;
    for (int i = 1, lower = 0, upper = 1; i < n; ++i) {
      int& res = _prefixs[i];
      res = upper <= i ? 0 : min(_prefixs[i - lower], upper - i);
      for (; i + res < n && pattern[res] == pattern[i + res]; ++res) {}
      if (i + res - 1 > upper) {
        lower = i;
        upper = i + res;
      }
    }
  }
#endif

  // prefixs[i]: represents the longest common prefix of pattern and pattern[i:]
  vector<int> _prefixs;
};

} // namespace str
