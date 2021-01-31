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

#define NTT_POLY_MOD_INT_MUL_INLINE
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "debug/debug.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "math/poly/ntt_poly_mod_int.h"

const int MAXM = (1000000 + 2) >> 1;
const int MOD = 7340033;

using V = int;
using V_SQR = int64_t;

int n, x, y, x1;
math::NTTPolyModInt<V, V_SQR, MOD, 5> xs, revXs;

int answers[MAXM];

int main() {
  io::readInt(n);
  io::readInt(x);
  io::readInt(y);
  x1 = x + 1;
  xs.resize(x1);
  revXs.resize(x1);
  for (int i = 0; i <= n; ++i) {
    int v;
    io::readInt(v);
    xs[v] = 1;
    revXs[x - v] = 1;
  }
  xs *= revXs;
  memset(answers, 0xFF, sizeof(answers));
  for (int i = x + 1, j = y + 1; i <= (x << 1) && j < MAXM; ++i, ++j) {
    if (i < xs.size() && xs[i]._v && j < MAXM) {
      for (int k = j; k < MAXM; k += j) {
        answers[k] = j << 1;
      }
    }
  }
  int q;
  io::readInt(q);
  for (int i = 0; i < q; ++i) {
    int x;
    io::readInt(x);
    io::writeInt(answers[x >> 1]);
    io::writeChar(i + 1 == q ? '\n' : ' ');
  }
  return 0;
}
