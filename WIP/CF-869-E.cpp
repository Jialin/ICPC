// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_FENWICK_2D_ARRAY_CALC_PREFIX
#include "ds/fenwick/base_fenwick_2d_array_macros.h"
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_MUL
#define MOD_INT_NEGATE
#include "math/mod/mod_int_macros.h"

#include "ds/fenwick/fenwick_2d_array_sum.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "math/mod/mod_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 2500;
const int MOD = 1000000007;

using ModInt = math::ModInt<int, int64_t, MOD>;
ModInt BASE(31);

ds::Fenwick2DArraySum<ModInt, MAXN, MAXN> fen;

int main() {
  int n, m, q;
  io::readInt(n);
  io::readInt(m);
  io::readInt(q);
  fen.init(n, m);
  vector<ModInt> hvs(q);
  hvs[0]._v = 1;
  unordered_map<int64_t, int> queryIdxs;
  FOR(i, 0, q) {
    if (i) {
      hvs[i].initMul(hvs[i - 1], BASE);
    }
    int op, x1, y1, x2, y2;
    io::readInt(op);
    io::readInt(x1);
    io::readInt(y1);
    io::readInt(x2);
    io::readInt(y2);
    if (op == 1) {
      auto queryHv = (((((x1 << 12) | CAST<int64_t>(y1)) << 12) | x2) << 12) | y2;
      queryIdxs[queryHv] = i;
      fen.update(x1 - 1, y1 - 1, hvs[i]);
      fen.update(x2, y2, hvs[i]);
      fen.update(x1 - 1, y2, -hvs[i]);
      fen.update(x2, y1 - 1, -hvs[i]);
    } else if (op == 2) {
      auto queryHv = (((((x1 << 12) | CAST<int64_t>(y1)) << 12) | x2) << 12) | y2;
      const auto it = queryIdxs.find(queryHv);
      assert(it != queryIdxs.end());
      const auto& delta = hvs[it->second];
      fen.update(x1 - 1, y1 - 1, -delta);
      fen.update(x2, y2, -delta);
      fen.update(x1 - 1, y2, delta);
      fen.update(x2, y1 - 1, delta);
    } else {
      io::writeCharArray(fen.calcPrefix(x1, y1)._v == fen.calcPrefix(x2, y2)._v ? "Yes\n" : "No\n");
    }
  }
  return 0;
}
