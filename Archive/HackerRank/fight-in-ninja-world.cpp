// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_PARITY_RESERVE
#include "ds/disjoint_set/disjoint_set_size_parity_macros.h"

#include "ds/disjoint_set/disjoint_set_size_parity.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 20000;

ds::DisjointSetSizeParity dset;
int totalCnt[MAXN], oddCnt[MAXN];

int main() {
  dset.reserve(MAXN);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n;
    io::readInt(n);
    dset.init(MAXN);
    memset(totalCnt, 0xFF, sizeof(totalCnt));
    FOR(_, 0, n) {
      int a, b;
      io::readInt(a);
      io::readInt(b);
      totalCnt[--a] = totalCnt[--b] = 0;
      bool valid;
      dset.unionSet(a, b, true, valid);
      assert(valid);
    }
    memset(oddCnt, 0, sizeof(oddCnt));
    FOR(i, 0, MAXN) {
      if (totalCnt[i] < 0) {
        continue;
      }
      int j = dset.findSet(i);
      ++totalCnt[j];
      oddCnt[j] += dset._parities[i];
    }
    int res = 0;
    FOR(i, 0, MAXN) {
      if (totalCnt[i] > 0) {
        res += max(oddCnt[i], totalCnt[i] - oddCnt[i]);
      }
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(": ");
    io::writeInt(res);
    io::writeChar('\n');
  }
  return 0;
}
