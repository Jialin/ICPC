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
#define POLY_MOD_INT_ASSIGN
#define POLY_MOD_INT_CLEAR
#define POLY_MOD_INT_EMPLACE_BACK
#define POLY_MOD_INT_NTT_INLINE
#define POLY_MOD_INT_RESERVE
#define POLY_MOD_INT_RESIZE
#define POLY_MOD_INT_SHRINK
#define POLY_MOD_INT_SIZE
#define MOD_INT_ADD_INLINE
#define MOD_INT_DIV
#include "math/poly/poly_mod_int_macros.h"

#include "math/poly/poly_mod_int.h"

#include "debug/debug.h"

// e^(ax) = sum(a^k / k! * x^k, k >= 0)
//
// product(1 + e^(V_i * y) * x^C_i)
//
// dp[0][0] = e^0 * x
// dp[i][j] = dp[i - 1][j] + dp[i - 1][j - C_i] * e^(V_i * x)

const int MAXN = 128;
const int MAXPOW2 = 1 << 12;
const int MOD = 998244353;
const int ROOT = 31;

using ModInt = math::ModInt<int, int64_t, MOD>;
using PolyModInt = math::PolyModInt<int, int64_t, MOD>;

int n, budget, e, costs[MAXN], values[MAXN];

PolyModInt row[MAXN], product, cell;
math::NTTUtilsFix<int, int64_t, MOD, ROOT> ntt(MAXPOW2);
vector<ModInt> invFacts;

int main() {
  while (scanf("%d%d%d", &n, &budget, &e) != EOF) {
    invFacts.resize(e + 1);
    invFacts[0] = 1;
    for (int i = 1; i <= e; ++i) {
      invFacts[i] = invFacts[i - 1] / i;
    }
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &costs[i], &values[i]);
    }
    int pow2 = math::nextPow2_32((e + 1) << 1);
    for (int i = 0; i <= budget; ++i) {
      row[i].clear();
      row[i].reserve(pow2);
    }
    row[0].assign(1, 1);
    cell.reserve(pow2);
    product.reserve(pow2);
    for (int i = 0; i < n; ++i) {
      product.resize(e + 1);
      product[0] = 1;
      for (int j = 1; j <= e; ++j) {
        product[j] = product[j - 1] * values[i];
      }
      for (int j = 1; j <= e; ++j) {
        product[j] *= invFacts[j];
      }
      product.nttInline(false, pow2, ntt);
      for (int j = budget - costs[i]; j >= 0; --j) {
        cell = row[j];
        cell.nttInline(false, pow2, ntt);
        for (int k = 0; k < pow2; ++k) {
          cell[k] *= product[k];
        }
        cell.nttInline(true, pow2, ntt);
        if (cell.size() > e) {
          cell.resize(e + 1);
        }
        cell.shrink();
        for (; row[j + costs[i]].size() < cell.size();
             row[j + costs[i]].emplace_back(0)) {}
        for (size_t k = 0; k < cell.size(); ++k) {
          row[j + costs[i]][k] += cell[k];
        }
      }
    }
    ModInt res = 0;
    for (int i = 0; i <= budget; ++i) {
      if (e < row[i].size()) {
        res += row[i][e];
      }
    }
    printf("%d\n", (res / invFacts[e])._v);
  }
}
