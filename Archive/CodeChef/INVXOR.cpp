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
#include "math/mod/add.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/log.h"
#include "math/mod/sub.h"

const int MAXL = 10000 + 10;
const int RES_MOD = 998244353;

char nStr[MAXL];
int nLength, X, MOD, pow2N1;
math::LogMod<> logMod(100003, true, 100000);

inline int pow2N(int mod) {
  int res = math::fixMod(1, mod);
  for (int i = 0; i < nLength; ++i) {
    res = math::expMod(res, 10, mod);
    res = math::mulMod(res, math::fixMod(1 << (nStr[i] - '0'), mod), mod);
  }
  return res;
}

// - bits are independent
// - if popcount(OR(values)) is p,
//   - the beauty of sequence is OR(values)*2^(N-1)
//   - # of sequence is (2^N-1)^p
inline int calcP() {
  int xBase = math::subMod(
      math::addMod(pow2N1, pow2N1, MOD), math::fixMod(1, MOD), MOD);
  if (!xBase) {
    return X ? -1 : 1;
  }
  bool exist;
  int res = logMod.calc(xBase, X, MOD, exist);
  return exist ? res : -1;
}

// !!! Corner case !!!
// - When remainder=0,
//   - N = 1, no solution
//   - Otherwise, 1
inline int calc() {
  if (MOD == 1 || X == 1) {
    return 0;
  }
  if (!X) {
    return nLength == 1 && nStr[0] == '0' ? -1 : 1;
  }
  int p = calcP();
  if (p < 0) {
    return p;
  }
  return math::mulMod(
      math::subMod(math::expMod(2, p, RES_MOD), 1, RES_MOD),
      pow2N(RES_MOD),
      RES_MOD);
}

int main() {
  logMod.init(100003);
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    scanf("%s%d%d", nStr, &X, &MOD);
    nLength = strlen(nStr);
    for (int i = nLength - 1; i >= 0; --i) {
      if (nStr[i] == '0') {
        nStr[i] = '9';
      } else {
        --nStr[i];
        break;
      }
    }
    pow2N1 = pow2N(MOD);
    printf("%d\n", calc());
  }
  return 0;
}