// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/sparse_table/base_disjoint_sparse_table.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"
#include "math/bit/next_pow2_32.h"
#include "math/mod/add.h"
#include "math/mod/mul.h"

// Last include
#include "debug/debug.h"

int MOD;

template<int MAXNBIT, int MAXN>
struct ProductModDisjointSparseTable : ds::BaseDisjointSparseTable<int, MAXNBIT, MAXN> {
  inline void combine(const int& leftValue, const int& rightValue, int& res) const override {
    res = math::mulMod(leftValue, rightValue, MOD);
  }
};

const int MAXN = 1000000;
const int MAXQB = (20000000 >> 6) + 2;

int n;
vector<int> as, bs;
ProductModDisjointSparseTable<21, MAXN> st;

int main() {
  as.reserve(MAXN);
  bs.reserve(MAXQB);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int q;
    io::readInt(n);
    io::readInt(MOD);
    io::readInt(q);
    as.resize(n);
    FOR(i, 0, n) {
      io::readInt(as[i]);
      math::fixModInline(as[i], MOD);
    }
    st.init(as);
    bs.resize((q >> 6) + 2);
    for (auto& b : bs) {
      io::readInt(b);
    }
    int res = 0;
    int lower, upper;
    FOR(i, 0, q) {
      math::fixModInline(res, n);
      if (!(i & 63)) {
        lower = math::addMod(bs[i >> 6], res, n);
        upper = math::addMod(bs[(i >> 6) + 1], res, n);
      } else {
        lower = math::addMod(lower, res, n);
        upper = math::addMod(upper, res, n);
      }
      if (lower > upper) {
        swap(lower, upper);
      }
      st.calc(lower, upper + 1, res);
      res = math::addMod(res, 1, MOD);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
