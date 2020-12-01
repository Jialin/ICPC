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
#include "math/gcd/gcd.h"
#include "math/mod/log_coprime.h"
#include "math/mod/mul.h"

const int HASH_SIZE = 1000003;
const int HASH_KEY_CNT = 2000000;
const int BOUND = 10000;

const int MOD = 100000007;
const int PHI = MOD - 1;
const int ROOT = 5;

math::LogModCoPrime<> logMod;
vector<int> logs;
vector<pair<int, int>> vs;

// Assume g to be primitive root
//   g^logBase = base (mod MOD)
//   g^logSmall = value (mod MOD)
//   base^x=value (mod MOD)
// Then we have,
//   g^(logBase*x-logSmall)=1 (mod MOD)
//   logBase*x=logSmall (mod phi(MOD))

inline int64_t calc(int base) {
  int64_t res = 0;
  int curMin = MOD;
  for (int curV = base; curMin >= BOUND; curV = math::mulMod(curV, base, MOD)) {
    if (curMin <= curV) {
      continue;
    }
    curMin = curV;
    res += curV;
    DEBUGF("curV:%d\n", curV);
  }
  if (curMin == 1) {
    return res;
  }
  bool exist;
  int logBase = logMod.calcFixedBaseMod(base, exist);
  DEBUG_TRUE(exist, "exist should always be true", exist);
  int gcd = math::gcd(logBase, PHI);
  int rLogBase = logBase / gcd;
  int phi = PHI / gcd;
  int invRLogBase = math::invMod(math::fixMod(rLogBase, phi), phi);
  int pos = MOD;
  for (int i = 1; i < curMin; ++i) {
    if (logs[i] % gcd) {
      continue;
    }
    int newPos =
        math::mulMod(math::fixMod(logs[i] / gcd, phi), invRLogBase, phi);
    if (!newPos) {
      newPos = phi;
    }
    if (pos > newPos) {
      pos = newPos;
      res += i;
      DEBUGF("pos:%d curV:%d\n", pos, i);
    }
  }
  return res;
}

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  vs.reserve(HASH_KEY_CNT);
  logMod.init(HASH_SIZE, true, HASH_KEY_CNT);
  logMod.precomputeFixedBaseMod(
      ROOT, MOD, static_cast<int>(sqrt(MOD) * sqrt(BOUND) + 1));
  logs.assign(BOUND, 0);
  for (int i = 1; i < BOUND; ++i) {
    bool exist;
    logs[i] = logMod.calcFixedBaseMod(i, exist);
    DEBUG_TRUE(exist, "exist should always be true", exist);
  }
  DEBUGF("logs[1]:%d\n", logs[1]);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int base;
    scanf("%d", &base);
    printf("%lld\n", calc(base));
  }
  return 0;
}