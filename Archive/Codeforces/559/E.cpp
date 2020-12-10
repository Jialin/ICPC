#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
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

#include "debug/debug.h"
#include "math/bit/submasks.h"

const int MAXN = 13;
const int MAXMASK = 1 << MAXN;
const int MAXR = 100;

int n, m, r;
int adjMasks[MAXN], descendantMasks[MAXN];
bool invalidSplit[MAXN][MAXMASK];
int64_t dp[MAXN][MAXMASK];
bool isValidSingle[MAXMASK];

// - edges:
//   - when splits, the adjcent nodes of the choosen root had to be covered by
//   mask or current root
// - lca:
//   - decendent and ancestor relations
//   - when chosen root is lca, child need to be splitted into different trees
//
// dp[root][mask]: root is not in mask
//   - choose a submask and root in submask, that need to cover mask min bits
//     += dp[root'][submask] * dp[root][mask ^ submask]

inline int64_t calc(int root, int mask) {
  if (dp[root][mask] >= 0) {
    return dp[root][mask];
  }
  if (!mask) {
    return 1;
  }
  int64_t& res = dp[root][mask];
  res = 0;
  int lastBit = __builtin_ctz(mask);
  math::submasks(
      mask ^ (1 << lastBit), [&res, lastBit, mask, root](int submask) {
        submask |= 1 << lastBit;
        if (invalidSplit[root][submask]) {
          return true;
        }
        for (int remMask = submask; remMask;) {
          int bit = __builtin_ctz(remMask);
          if ((adjMasks[bit] & ((1 << root) | submask)) == adjMasks[bit] &&
              (descendantMasks[bit] & submask) == descendantMasks[bit]) {
            res += calc(bit, submask ^ (1 << bit)) * calc(root, mask ^ submask);
          }
          remMask ^= 1 << bit;
        }
        return true;
      });
  return res;
}

int main() {
  while (scanf("%d%d%d", &n, &m, &r) != EOF && n) {
    memset(adjMasks, 0, sizeof(adjMasks));
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x;
      --y;
      adjMasks[x] |= 1 << y;
      adjMasks[y] |= 1 << x;
    }
    memset(descendantMasks, 0, sizeof(descendantMasks));
    memset(invalidSplit, 0, sizeof(invalidSplit));
    bool invalid = false;
    for (int i = 0; i < r; ++i) {
      int u, v, lca;
      scanf("%d%d%d", &u, &v, &lca);
      --u;
      --v;
      --lca;
      if (u == v && u != lca) {
        invalid = true;
      }
      if (u != lca) {
        descendantMasks[lca] |= 1 << u;
      }
      if (v != lca) {
        descendantMasks[lca] |= 1 << v;
      }
      if (u != lca && v != lca) {
        int crossMask = (1 << u) | (1 << v);
        for (int mask = 1; mask < 1 << n; ++mask) {
          if (__builtin_popcount(mask & crossMask) == 2) {
            invalidSplit[lca][mask] = true;
          }
        }
      }
    }
    memset(dp, 0xFF, sizeof(dp));
    printf("%lld\n", invalid ? 0 : calc(0, ((1 << n) - 1) ^ 1));
  }
  return 0;
}