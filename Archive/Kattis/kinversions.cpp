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

#define POLY_MOD_INT_ACCESS
#define POLY_MOD_INT_MUL_INLINE_MODIFY
#define POLY_MOD_INT_RESIZE
#define POLY_MOD_INT_SIZE
#include "math/poly/poly_mod_int_macros.h"

#include "debug/debug.h"
#include "io/read_char_array.h"
#include "io/write_int.h"
#include "math/poly/poly_mod_int.h"

const int MAXN = 1000000 + 2;
const int MOD = 998244353;

int n;
char s[MAXN];
math::PolyModInt<int, int64_t, MOD> as, bs;
math::NTTUtilsFix<int, int64_t, MOD, 31> ntt(MAXN << 1);

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
  as.mulInlineModify(bs, false, ntt);
  for (size_t i = n; i < (n << 1) - 1; ++i) {
    io::writeInt(i < as.size() ? as[i]._v : 0);
    io::writeChar('\n');
  }
}
