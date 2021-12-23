// !macro_gen
// ALL MANACHER_ALL
#pragma once

#include "common/macros.h"
#include "string/palindrome/manacher_macros.h"

#include "string/palindrome/manacher.h"

using namespace std;

namespace str {

struct Manacher {
#ifdef MANACHER_RESERVE // ^
  inline void reserve(int n) {
    rs.reserve((n << 1) | 1);
  }
#endif

#ifdef MANACHER_CALC_CHAR_ARRAY // ^
  inline void calc(int n, char* s) {
    _calc(n, s, (n << 1) | 1);
  }
#endif

#ifdef MANACHER_CALC_STRING // ^
  inline void calc(const string& s) {
    _calc(s.size(), s.data(), (s.size() << 1) | 1);
  }
#endif

#ifdef MANACHER_ODD_LOWER // ^
  inline int oddLower(int i) {
    return i - (rs[(i << 1) | 1] >> 1) + 1;
  }
#endif

#ifdef MANACHER_ODD_UPPER // ^
  inline int oddUpper(int i) {
    return i + (rs[(i << 1) | 1] >> 1);
  }
#endif

#ifdef MANACHER_ODD_SIZE // ^
  inline int oddSize(int i) {
    return (rs[(i << 1) | 1] & ~1) - 1;
  }
#endif

#ifdef MANACHER_EVEN_LOWER // ^
  inline int evenLower(int i) {
    return i - (rs[i << 1] >> 1);
  }
#endif

#ifdef MANACHER_EVEN_UPPER // ^
  inline int evenUpper(int i) {
    return i + (rs[i << 1] >> 1);
  }
#endif

#ifdef MANACHER_EVEN_SIZE // ^
  inline int evenSize(int i) {
    return rs[i << 1] & ~1;
  }
#endif

#ifdef MANACHER_LONGEST_PALINDROME // ^
  inline pair<int, int> longestPalindrome() {
    int res = 0, idx = 0;
    FOR(i, 1, SIZE(rs)) {
      int subRes = (rs[i] & ~1) - (i & 1);
      if (res < subRes) {
        res = subRes;
        idx = i;
      }
    }
    return {(idx >> 1) - (rs[idx] >> 1) + (idx & 1), (idx >> 1) + (rs[idx] >> 1)};
  }
#endif

  inline void _calc(int n, const char* s, int upper) {
    int n2p1 = (n << 1) | 1;
    rs.resize(n2p1);
    for (int i = 0, l = 0, r = 0; i < upper; ++i) {
      int j = i >= r ? 0 : min(rs[r - i - 1 + l], r - i);
      int bound = min(i, n2p1 - 1 - i);
      if (!((i - j) & 1)) {
        ++j;
      }
      for (int x = (i - j) >> 1, y = (i + j) >> 1; j <= bound && s[x] == s[y]; j += 2, --x, ++y) {}
      MMIN(j, bound + 1);
      rs[i] = j;
      if (r < i + j) {
        l = i - j + 1;
        r = i + j;
      }
    }
    fill(rs.begin() + upper, rs.end(), 0);
  }

  vector<int> rs;
};

} // namespace str
