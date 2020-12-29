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

#define MOD_INT_MUL
#define NTT_UTILS_FIX_MOD_MUL_INLINE
#include "math/fft/ntt_utils_fix_mod_macros.h"

#include "debug/debug.h"
#include "math/fft/ntt_utils_fix_mod.h"

const int MAXNK = 2000000 + 2;
const int MAXPOW2 = 1 << 22;
const int MOD = 998244353;

using ModInt = math::ModInt<int, int64_t, MOD>;

int n, k, a[MAXNK];
ModInt facts[MAXNK], invFacts[MAXNK];
math::NTTUtilsFixMod<int, int64_t, MOD, 31> ntt(MAXPOW2);

// f(i) = sum(f(j) * e^{sum(a[k], k from j+1 to i)}x , j from 0 to i - 1)

// f(i) = sum{ e^sum(a[k], k from j to i), j from 0 to i}

int main() {
  scanf("%d%d", &n, &k);
  facts[0] = 1;
  for (int i = 1; i <= k; ++i) {
    facts[i] = facts[i - 1] * i;
  }
  invFacts[k] = facts[k].inv();
  for (int i = k; i > 0; --i) {
    invFacts[i - 1] = invFacts[i] * i;
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  vector<ModInt> res;
  vector<ModInt> expSum(1);
  for (int i = 0; i < n; ++i) {
    vector<ModInt> ex(k + 1);
    ModInt pow = 1;
    ex[0] = pow;
    for (int j = 1; j <= k; ++j) {
      pow *= a[i];
      ex[j] = pow * invFacts[j];
    }
    expSum[0] += 1;
    ntt.mulInline(expSum, ex);
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
    printf("%d%c", (res[i] * facts[i])._v, i == k ? '\n' : ' ');
  }
}
