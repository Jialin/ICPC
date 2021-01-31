// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define MOD_INT_INIT_MUL
#define MOD_INT_DIV_INLINE
#define MOD_INT_MUL
#define NTT_POLY_MOD_INT_CONSTRUCT
#define NTT_POLY_MOD_INT_ONLINE_INLINE
#include "math/mod/mod_int_macros.h"
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "io/write_int.h"
#include "math/mod/mod_int.h"
#include "math/poly/ntt_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000 + 1;
const int MAXM = 50 + 1;
const int MOD = 924844033;
const int ROOT = 3597;
const int MAXPOW2 = 1 << 18;

using ModInt = math::ModInt<int, int64_t, MOD>;
using NTTPolyModInt = math::NTTPolyModInt<int, int64_t, MOD, ROOT>;

int n, m;
ModInt fact[MAXN], invFact[MAXN];
ModInt colorWays[MAXM][MAXN];
NTTPolyModInt bases;

// labeled trees:
// - a(i)=i^(i-2) for i>=2
// - a(i)=1       for i<2
//
// color n nodes with m distinct color
// - b(i,j)=b(i-1,j-1)+b(i-1,j)*j for j>1
// - b(i,1)=1
//
// - f(i)=sum(C(i-1,j-1)*f(i-j)*b(j), j from 1 to i)
// - f(i)=sum((i-1)!/(i-j)!/(j-1)!*f(i-j)*b(j))
// - f(i)*i/i!=sum(f(i-j)/(i-j)!*b(j)/(j-1)!)
//
// - g(i)=f(i)/i!
// - c(j)=b(j)/(j-1)!
// - g(i)*i=sum(g(j)*c(j))
//
// f(n)*n=sum(f(i)*g(n-i),i from 1 to n-1)
// F'x+F=F*G
// F'x=G(F-1)
// F'/(F-1)=G/x
// ln'(F-1)=G/x
//
// ln(F-1)=integ(G/x)
// F-1=exp(integ(G/x))
//
// Alternative:
// - a[i]=S[i][m]*m!*i^(i-2)/i!

int main() {
  math::NTTUtils<int, int64_t, MOD, ROOT>::instance().initCapacity(MAXPOW2);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    colorWays[1][i] = 1;
  }
  for (int i = 2; i <= m; ++i) {
    for (int j = i; j <= n; ++j) {
      colorWays[i][j] = (colorWays[i][j - 1]._v + colorWays[i - 1][j - 1]._v) * CAST<int64_t>(i);
    }
  }
  fact[0] = 1;
  FOR(i, 1, n + 1) {
    fact[i].initMul(fact[i - 1], i);
  }
  invFact[n] = fact[n].inv();
  for (int i = n - 1; i >= 0; --i) {
    invFact[i].initMul(invFact[i + 1], i + 1);
  }
  bases.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (i >= m) {
      bases[i] = colorWays[m][i] * ModInt(i).exp(max(i - 2, 0)) * invFact[i - 1];
    } else {
      bases[i] = 0;
    }
  }
  NTTPolyModInt answers(1, 1);
  answers.onlineInline(bases, 1, n + 1, [](ModInt& f, int idx) {
    f /= idx;
  });
  for (int i = 1; i <= n; ++i) {
    answers[i] *= fact[i];
    io::writeInt(answers[i]._v);
    io::writeChar('\n');
  }
}
