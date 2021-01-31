// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define NTT_POLY_MOD_INT_MUL_INLINE
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "io/read_char_array.h"
#include "io/write_int.h"
#include "math/poly/ntt_poly_mod_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 1000000 + 2;
const int MOD = 998244353;

int n;
char s[MAXN];
math::NTTPolyModInt<int, int64_t, MOD, 31> as, bs;

int main() {
  n = io::readCharArray(s);
  as.resize(n);
  bs.resize(n);
  for (int i = 0, j = n - 1; i < n; ++i, --j) {
    if (s[i] == 'A') {
      as[i] = 1;
    } else {
      bs[j] = 1;
    }
  }
  as *= bs;
  for (size_t i = n; i < (n << 1) - 1; ++i) {
    io::writeInt(i < as.size() ? as[i]._v : 0);
    io::writeChar('\n');
  }
}
