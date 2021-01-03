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

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/write_int.h"

const int MAXL = 125000 + 1;
const int MOD = 1000000007;
const int MAXC = 6;
const int MAXMASK = 1 << MAXC;

uint64_t powMod[MAXL], hashS[MAXMASK], hashT[MAXMASK];
char s[MAXL], t[MAXL];
int n, m;
vector<int> sortedMasks;

int main() {
  powMod[0] = 1;
  for (int i = 1; i < MAXL; ++i) {
    powMod[i] = powMod[i - 1] * MOD;
  }
  sortedMasks.resize(MAXMASK);
  for (int i = 0; i < MAXMASK; ++i) {
    sortedMasks[i] = i;
  }
  sort(sortedMasks.begin(), sortedMasks.end(), [](int x, int y) {
    return __builtin_popcount(x) < __builtin_popcount(y);
  });
  n = io::readCharArray(s);
  m = io::readCharArray(t);
  for (int i = 0; i < m; ++i) {
    int idx = t[i] - 'a';
    for (int mask = 0; mask < MAXMASK; ++mask) {
      if (mask & (1 << idx)) {
        hashT[mask] += powMod[i];
      }
    }
  }
  for (int i = 0; i < m - 1; ++i) {
    int idx = s[i] - 'a';
    for (int mask = 0; mask < MAXMASK; ++mask) {
      if (mask & (1 << idx)) {
        hashS[mask] += powMod[i];
      }
    }
  }
  for (int i = m - 1, j = 0; i < n; ++i, ++j) {
    int idx = s[i] - 'a';
    for (int mask = 0; mask < MAXMASK; ++mask) {
      if (mask & (1 << idx)) {
        hashS[mask] += powMod[i];
      }
    }
    int coveredMask = 0, res = 0;
    for (int mask : sortedMasks) {
      if (mask & coveredMask) {
        continue;
      }
      if (!hashS[mask] && !hashT[mask]) {
        coveredMask |= mask;
        continue;
      }
      if (hashS[mask] == hashT[mask] * powMod[j]) {
        coveredMask |= mask;
        res += __builtin_popcount(mask) - 1;
      }
    }
    io::writeInt(res);
    io::writeChar(i + 1 == n ? '\n' : ' ');
    idx = s[j] - 'a';
    for (int mask = 0; mask < MAXMASK; ++mask) {
      if ((mask >> idx) & 1) {
        hashS[mask] -= powMod[j];
      }
    }
  }
}
