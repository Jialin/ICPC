// !macro_gen
// ALL BASE_DISJOINT_SPARSE_TABLE_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"
#include "math/bit/next_pow2_32.h"

using namespace std;

namespace ds {

template<typename V, int MAXNBIT, int MAXN>
struct BaseDisjointSparseTable {
  virtual inline void combine(const V& lv, const V& rv, V& res) const = 0;

  inline void init(const vector<V>& vs) {
    DEBUG_GE(1 << MAXNBIT, MAXN);
    int n = vs.size();
    int pow2 = math::nextPow2_32(n);
    _bit = __builtin_ctz(pow2);
    _dfs(0, 0, pow2, n, vs);
  }

#ifdef BASE_DISJOINT_SPARSE_TABLE_CALC // ^
  inline V calc(int lower, int upper) {
    V res;
    // BASE_DISJOINT_SPARSE_TABLE_CALC => _BASE_DISJOINT_SPARSE_TABLE_CALC
    _calc(lower, upper, res);
    return res;
  }
#endif

#ifdef _BASE_DISJOINT_SPARSE_TABLE_CALC // ^
  inline void _calc(int lower, int upper, V& res) const {
    if (lower + 1 == upper) {
      res = _st[_bit][lower];
      return;
    }
    int depth = _bit - 1 - (31 ^ __builtin_clz(lower ^ (upper - 1)));
    combine(_st[depth][lower], _st[depth][upper - 1], res);
  }
#endif

  inline void _dfs(int depth, int lower, int upper, int n, const vector<V>& vs) {
    if (n <= lower) {
      return;
    }
    if (lower + 1 == upper) {
      _st[depth][lower] = vs[lower];
      return;
    }
    int medium = (lower + upper) >> 1;
    if (medium < n) {
      _st[depth][medium] = vs[medium];
    }
    int bound = min(upper, n);
    FOR(i, medium + 1, bound) {
      combine(_st[depth][i - 1], vs[i], _st[depth][i]);
    }
    bound = min(medium, n);
    _st[depth][bound - 1] = vs[bound - 1];
    for (int i = bound - 2; i >= lower; --i) {
      combine(vs[i], _st[depth][i + 1], _st[depth][i]);
    }
    _dfs(depth + 1, lower, medium, n, vs);
    _dfs(depth + 1, medium, upper, n, vs);
  }

  int _bit;
  V _st[MAXNBIT][MAXN];
};

} // namespace ds
