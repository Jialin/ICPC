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
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

const int MAXN = 16;
const int MAXMASK = 1 << MAXN;

int n;
int adjMasks[MAXN], subsetMasks[MAXMASK], dp[MAXMASK];
vector<int> validSubsets;
int mask, lastBit;

int main() {
  validSubsets.reserve(MAXMASK);
  for (int taskIdx = 1;; ++taskIdx) {
    io::readInt(n);
    if (!n) {
      break;
    }
    for (int i = 0; i < n; ++i) {
      int m;
      io::readInt(m);
      adjMasks[i] = 0;
      for (int j = 0; j < m; ++j) {
        int k;
        io::readInt(k);
        adjMasks[i] |= 1 << k;
      }
    }
    subsetMasks[0] = 0;
    for (mask = 1; mask < 1 << n; ++mask) {
      lastBit = __builtin_ctz(mask);
      subsetMasks[mask] = subsetMasks[mask ^ (1 << lastBit)] |
                          adjMasks[lastBit] | (1 << lastBit);
    }
    memset(dp, 0, sizeof(int) << n);
    validSubsets.clear();
    for (mask = 1; mask < 1 << n; ++mask) {
      for (int submask : validSubsets) {
        if ((submask & mask) == submask) {
          dp[mask] = max(dp[mask], dp[mask ^ submask] + 1);
        }
      }
      if (!dp[mask] && subsetMasks[mask] + 1 == (1 << n)) {
        validSubsets.emplace_back(mask);
        dp[mask] = 1;
      }
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx);
    io::writeCharArray(": ");
    io::writeInt(*max_element(dp, dp + (1 << n)));
    io::writeChar('\n');
  }
  return 0;
}