// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_RESULTANT_MODIFY
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000007;

using Poly = math::FFTPolyModInt<double, int, int64_t, MOD>;

int n;
vector<int> a, pi;
vector<int> order0, order1;
unordered_map<int, int> order1Idx;
Poly aP, bP;

inline int calc() {
  int cnt = 1;
  for (int i = pi[0]; i; i = pi[i], ++cnt) {}
  if (cnt != n) {
    return 0;
  }
  order0.resize(n);
  order1.resize(n);
  FOR(i, 0, n) {
    order0[i] = i;
    order1[i] = pi[i];
    order1Idx[pi[i]] = i;
  }
  bool negate = false;
  FOR(i, 0, n) {
    int j = i + 1 == n ? 0 : i + 1;
    if (order1[j] == order0[i]) {
      continue;
    }
    negate = !negate;
    int k = order1Idx[order0[i]];
    swap(order1Idx[order1[i + 1]], order1Idx[order0[i]]);
    swap(a[j], a[k]);
    swap(order0[j], order0[k]);
    swap(order1[j], order1[k]);
  }
  aP.resize(n);
  FOR(i, 0, n) {
    aP[i] = a[i];
  }
  bP.assign(n + 1, 0);
  bP[0] = -1;
  bP[n] = 1;
  DEBUGV(aP);
  DEBUGV(bP);
  auto res = aP.resultantModify(bP);
  DEBUGV(res);
  if (negate) {
    res.negateInline();
  }
  return res._v;
}

int main() {
  scanf("%d", &n);
  a.resize(n);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }
  pi.resize(n);
  FOR(i, 0, n) {
    scanf("%d", &pi[i]);
    --pi[i];
  }
  printf("%d\n", calc());
}
