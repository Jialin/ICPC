// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_RESERVE
#define DISJOINT_SET_SIZE_UNION_SET
#include "ds/disjoint_set/disjoint_set_size_macros.h"

#include "ds/disjoint_set/disjoint_set_size.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 100000;
const int MAXQ = 100000;

int n;
ds::DisjointSetSize dset;
int as[MAXN], ops[MAXQ], idx1[MAXQ], idx2[MAXQ], lastIdx[MAXN];
vector<int> dis;

int main() {
  dset.reserve(MAXN);
  dis.reserve(MAXN + (MAXQ << 1));
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    io::readInt(n);
    int q;
    io::readInt(q);
    dis.clear();
    FOR(i, 0, n) {
      io::readInt(as[i]);
      dis.push_back(--as[i]);
    }
    FOR(i, 0, q) {
      io::readInt(ops[i]);
      io::readInt(idx1[i]);
      --idx1[i];
      if (ops[i] == 1) {
        io::readInt(idx2[i]);
        dis.push_back(idx1[i]);
        dis.push_back(--idx2[i]);
      }
    }
    SORTUNIQUE(dis);
    int disCnt = SIZE(dis);
    dset.init(n);
    memset(lastIdx, 0xFF, sizeof(int) * disCnt);
    FOR(i, 0, n) {
      int v = INDEX(dis, as[i]);
      if (lastIdx[v] >= 0) {
        dset.unionSet(lastIdx[v], i);
      }
      lastIdx[v] = i;
      as[i] = v;
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx + 1);
    io::writeCharArray(":\n");
    FOR(i, 0, q) {
      if (ops[i] == 1) {
        int x = INDEX(dis, idx1[i]);
        int y = INDEX(dis, idx2[i]);
        if (x == y || lastIdx[x] < 0) {
          continue;
        }
        if (lastIdx[y] >= 0) {
          dset.unionSet(lastIdx[x], lastIdx[y]);
        }
        as[dset.findSet(lastIdx[x])] = y;
        lastIdx[y] = lastIdx[x];
        lastIdx[x] = -1;
      } else {
        io::writeInt(dis[as[dset.findSet(idx1[i])]] + 1);
        io::writeChar('\n');
      }
    }
  }
  return 0;
}
