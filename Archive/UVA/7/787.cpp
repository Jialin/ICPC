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

#define BIGINT_ASSIGN_INT
#define BIGINT_LT
#define BIGINT_MUL_INLINE_INT
#define BIGINT_PRINT

#include "debug/debug.h"
#include "math/bigint.h"

const int MAXN = 100;

vector<int> vs;
bool zero;
math::BigInt<> res, res1, res2;
bool neg1, neg2, signoff;

inline bool calc() {
  if (vs.size() == 1 && vs[0] < 0) {
    res = abs(vs[0]);
    return true;
  }
  res = 0;
  res1 = 1;
  neg1 = false;
  signoff = false;
  for (int v : vs) {
    if (!v) {
      res1 = 1;
      neg1 = false;
      signoff = false;
      continue;
    }
    res1 *= abs(v);
    neg1 ^= v < 0;
    if (!neg1 && res < res1) {
      res = res1;
    }
    if (signoff) {
      res2 *= abs(v);
      neg2 ^= v < 0;
      if (!neg2 && res < res2) {
        res = res2;
      }
    } else if (v < 0) {
      signoff = true;
      res2 = 1;
      neg2 = false;
    }
  }
  return false;
}

int main() {
  vs.reserve(MAXN);
  int v;
  while (scanf("%d", &v) != EOF) {
    vs.clear();
    do {
      vs.push_back(v);
      scanf("%d", &v);
    } while (v != -999999);
    bool negative = calc();
    if (negative) {
      putchar('-');
    }
    res.print();
    putchar('\n');
  }
  return 0;
}
