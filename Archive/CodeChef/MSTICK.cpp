// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SPARSE_TABLE_ARRAY_RESERVE
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/max_sparse_table_array.h"
#include "ds/sparse_table/min_sparse_table_array.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

inline void printHalf(int res2) {
  io::writeInt(res2 >> 1);
  io::writeChar('.');
  io::writeChar((res2 & 1) ? '5' : '0');
  io::writeChar('\n');
}

ds::MinSparseTableArray<int, 17, 100000> minST;
ds::MaxSparseTableArray<int, 18, 199999> maxST;

int main() {
  int n;
  io::readInt(n);
  vector<int> minVs(n);
  vector<int> maxVs((n << 1) - 1);
  FOR(i, 0, n) {
    io::readInt(minVs[i]);
    maxVs[i] = minVs[i];
  }
  FOR(i, 0, n - 1) {
    maxVs[i + n] = maxVs[i];
  }
  minST.reserve(n);
  minST.init(move(minVs));
  maxST.reserve((n << 1) - 1);
  maxST.init(move(maxVs));
  int q;
  io::readInt(q);
  FOR(_, 0, q) {
    int l, r;
    io::readInt(l);
    io::readInt(r);
    ++r;
    int minV, maxInV;
    minST.calc(l, r, minV);
    maxST.calc(l, r, maxInV);
    if (l == 0 && r == n) {
      printHalf(minV + maxInV);
    } else {
      int maxOutV;
      maxST.calc(r, l + n, maxOutV);
      printHalf(max(minV + maxInV, (minV + maxOutV) << 1));
    }
  }
}
