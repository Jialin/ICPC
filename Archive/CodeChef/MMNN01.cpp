// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define FFT_POLY_MOD_INT_CONSTRUCT
#define FFT_POLY_MOD_INT_INV_INLINE
#define FFT_POLY_MOD_INT_SUB
#define MOD_INT_ADD_INLINE
#include "math/poly/fft_poly_mod_int_macros.h"

#include "io/read_int.h"
#include "io/write_int.h"
#include "math/poly/fft_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MOD = 1000000007;

using ModInt = math::ModInt<int, int64_t, MOD>;
using FFT_T = double;
using FFTPolyModInt = math::FFTPolyModInt<FFT_T, int, int64_t, MOD>;

// first flavor is fixed, then choose another i-1 distinct flavors, at last
// choose one of the a exsting i distinct flavor:
// - a(i)=C(M-1,i-1)*(i-1)!*i/M^i
//       =(M-1)!/(M-i)!*i/M^i
//
// - a(i-1)=(M-1)!/(M-i+1)!*(i-1)/M^(i-1)
// - a(i)=a(i-1)*(M-i+1)/(i-1)*i/M
//
// - e(i)+1=sum((e(j)+1)*p(i-j))+1
// - e1(i)=sum(e1(j)*p(i-j))+1
//
// E=E*P+I
// E(1-P)=I
// E(1-P)(x-1)=1
//
// {0}
// {1}
// e(1)=1    e1(1)=2
// {0,0} 2
// {0,1} 1
// {1,0} 1
// {1,1} 2
// e(2)=1.5  e2(2)=2.5
// {0,0,0} 3
// {0,0,1} 2
// {0,1,0} 2
// {0,1,1} 2
// {1,0,0} 2
// {1,0,1} 2
// {1,1,0} 2
// {1,1,1} 3
// e(3)=18/8
//
// Alternative:
// - a[0]=1
// - a[1]=M/M
// - a[2]=M(M-1)/M^2
//
// - a[i]=M!/(M-i)!/M^(i+1)*(-i)
int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, m;
    io::readInt(n);
    io::readInt(m);
    ModInt invM = ModInt(m).inv();
    ModInt cur = invM;
    FFTPolyModInt bases(n + 1);
    for (int i = 1; i < bases.size(); ++i) {
      cur *= invM;
      cur *= m - i + 1;
      bases[i] = cur;
    }
    for (int i = 1; i < bases.size(); ++i) {
      bases[i] *= i;
    }
    bases = FFTPolyModInt(1, 1) - bases;
    bases.invInline();
    ModInt res = 0;
    for (int i = 0; i < n; ++i) {
      res += bases[i];
    }
    io::writeInt(res._v);
    io::writeChar('\n');
  }
  return 0;
}
