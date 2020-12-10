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

const int MAXN = 100;
const int MAXM = 15;
const int MAXMASK = 1 << MAXM;

char s1[2], s2[2];
int n, mask, inMask, invalidMasks[MAXN], xs[MAXN], ys[MAXN];
bool isValidMasks[MAXMASK];
int dp[MAXMASK], dpFrom[MAXMASK];
int levels[MAXM];
vector<int> validMasks;

int main() {
  validMasks.reserve(MAXMASK);
  while (scanf("%d", &n) != EOF) {
    inMask = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%s%s", s1, s2);
      xs[i] = s1[0] - 'L';
      ys[i] = s2[0] - 'L';
      invalidMasks[i] = (1 << xs[i]) | (1 << ys[i]);
      inMask |= invalidMasks[i];
    };
    for (mask = 1; mask < MAXMASK; ++mask) {
      isValidMasks[mask] = (mask & inMask) == mask;
      for (int i = 0; i < n && isValidMasks[mask]; ++i) {
        if ((mask & invalidMasks[i]) == invalidMasks[i]) {
          isValidMasks[mask] = false;
        }
      }
    }
    validMasks.clear();
    dp[0] = 0;
    for (mask = 1; mask < MAXMASK; ++mask) {
      if ((mask & inMask) != mask) {
        continue;
      }
      dp[mask] = MAXM + 1;
      for (int submask : validMasks) {
        if ((mask & submask) == submask && dp[mask] > dp[mask ^ submask] + 1) {
          dp[mask] = dp[mask ^ submask] + 1;
          dpFrom[mask] = submask;
        }
      }
      if (isValidMasks[mask]) {
        validMasks.emplace_back(mask);
        dp[mask] = 1;
        dpFrom[mask] = mask;
      }
    }
    int level = 0;
    for (mask = inMask; mask > 0; ++level) {
      int submask = dpFrom[mask];
      for (int i = 0; i < MAXM; ++i) {
        if (submask & (1 << i)) {
          levels[i] = level;
        }
      }
      mask ^= submask;
    }
    printf("%d\n", dp[inMask] - 2);
    for (int i = 0; i < n; ++i) {
      int x, y;
      if (levels[xs[i]] < levels[ys[i]]) {
        x = xs[i];
        y = ys[i];
      } else {
        x = ys[i];
        y = xs[i];
      }
      putchar(x + 'L');
      putchar(' ');
      putchar(y + 'L');
      putchar('\n');
    }
  }
  return 0;
}