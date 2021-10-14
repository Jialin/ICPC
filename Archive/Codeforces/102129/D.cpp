// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_INIT_POW_MOD_MEMO
#define FFT_POLY_MOD_INT_INV_INLINE
#define MATRIX_MOD_INT_SOLVE_MODIFY
#include "math/matrix/matrix_mod_int_macros.h"
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/matrix/matrix_mod_int.h"
#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000007;

using Poly = math::FFTPolyModInt<double, int, int64_t, MOD>;
using ModInt = math::ModInt<int, int64_t, MOD>;

Poly aMod, invResAMod, b, bRes;

math::MatrixModInt<int, int64_t, MOD> cM;
vector<ModInt> bV, res;
vector<Poly> bPowMemo;

int main() {
  int n;
  scanf("%d", &n);
  aMod.resize(n + 1);
  aMod[0] = 1;
  FOR(i, 0, n) {
    int v;
    scanf("%d", &v);
    aMod[i + 1] = -v;
  }
  invResAMod = aMod;
  reverse(invResAMod.begin(), invResAMod.end());
  invResAMod.invInline();
  cM.init(n, n);
  b.assign(2, 0);
  b[1] = 1;
  bPowMemo.reserve(32);
  FOR(i, 0, n) {
    int v;
    scanf("%d", &v);
    bRes.initPowModMemo(b, aMod, invResAMod, v, bPowMemo);
    FOR(j, 0, n) {
      if (j < bRes.size()) {
        cM[j][i] = bRes[j];
      } else {
        cM[j][i] = 0;
      }
    }
  }
  bV.assign(n, 0);
  bV[0] = 1;
  cM.solveModify(bV, res);
  FOR(i, 0, n) {
    printf("%d%c", res[i]._v, i + 1 == n ? '\n' : ' ');
  }
}
