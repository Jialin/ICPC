#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define POLY_MOD_INT_ACCESS
#define POLY_MOD_INT_CONSTRUCT
#define POLY_MOD_INT_EMPLACE_BACK
#define POLY_MOD_INT_MUL_INLINE_MODIFY
#define POLY_MOD_INT_RESIZE
#define POLY_MOD_INT_SIZE
#define MOD_INT_ADD_INLINE
#define MOD_INT_MUL
#include "math/poly/poly_mod_int_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/poly/poly_mod_int.h"

const int MAXNK = 2000000 + 2;
const int MOD = 998244353;

using ModInt = math::ModInt<int, int64_t, MOD>;
using PolyModInt = math::PolyModInt<int, int64_t, MOD>;

int n, k, a[MAXNK];
ModInt facts[MAXNK], invFacts[MAXNK];
math::NTTUtilsFix<int, int64_t, MOD, 31> ntt;

// f(i) = sum(f(j) * e^{sum(a[k], k from j+1 to i)}x , j from 0 to i - 1)
// f(i) = sum{ e^sum(a[k], k from j to i), j from 0 to i}

int main() {
  io::readInt(n);
  io::readInt(k);
  ntt.init((k + 1) << 1);
  facts[0] = 1;
  for (int i = 1; i <= k; ++i) {
    facts[i] = facts[i - 1] * i;
  }
  invFacts[k] = facts[k].inv();
  for (int i = k; i > 0; --i) {
    invFacts[i - 1] = invFacts[i] * i;
  }
  for (int i = 0; i < n; ++i) {
    io::readInt(a[i]);
  }
  PolyModInt res, expSum(1);
  for (int i = 0; i < n; ++i) {
    PolyModInt ex(k + 1);
    ModInt pow = 1;
    ex[0] = pow;
    for (int j = 1; j <= k; ++j) {
      pow *= a[i];
      ex[j] = pow * invFacts[j];
    }
    expSum[0] += 1;
    expSum.mulInlineModify(ex, false, ntt);
    if (expSum.size() > k) {
      expSum.resize(k + 1);
    }
    for (; res.size() < expSum.size(); res.emplace_back(0)) {}
    for (int j = 0; j <= k; ++j) {
      if (j < ex.size()) {
        res[j] += expSum[j];
      }
    }
  }
  for (int i = 1; i <= k; ++i) {
    io::writeInt((res[i] * facts[i])._v);
    io::writeChar(i == k ? '\n' : ' ');
  }
}
