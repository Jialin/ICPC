// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define MOD_INT_ADD_INLINE
#define MOD_INT_DIV
#define MOD_INT_MUL
#define MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#define NTT_UTILS_NTT_MOD_INT
#include "math/fft/ntt_utils_macros.h"
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "math/fft/ntt_utils.h"
#include "math/poly/ntt_poly_mod_int.h"

// Last include
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

int n, budget, e, costs[MAXN], values[MAXN];
math::NTTPolyModInt<int, int64_t, MOD, ROOT> row[MAXN], product, cell;
vector<ModInt> invFacts;

int main() {
  auto& ntt = math::NTTUtils<int, int64_t, MOD, ROOT>::instance();
  ntt.initCapacity(MAXPOW2);
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
      ntt.nttModInt(product, false, pow2);
      for (int j = budget - costs[i]; j >= 0; --j) {
        cell = row[j];
        ntt.nttModInt(cell, false, pow2);
        for (int k = 0; k < pow2; ++k) {
          cell[k] *= product[k];
        }
        ntt.nttModInt(cell, true, pow2);
        if (cell.size() > e) {
          cell.resize(e + 1);
        }
        cell.shrink();
        for (; row[j + costs[i]].size() < cell.size(); row[j + costs[i]].emplace_back(0)) {}
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
