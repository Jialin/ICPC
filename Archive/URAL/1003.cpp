// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define DISJOINT_SET_SIZE_PARITY_RESERVE
#include "ds/disjoint_set/disjoint_set_size_parity_macros.h"

#include "ds/disjoint_set/disjoint_set_size_parity.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXQ = 5000;
const int MAXQ2 = MAXQ << 1;

vector<int> dis, us, vs;
vector<bool> parities;
ds::DisjointSetSizeParity dset;
char state[10];

int main() {
  dis.reserve(MAXQ2);
  us.reserve(MAXQ);
  vs.reserve(MAXQ);
  parities.reserve(MAXQ);
  dset.reserve(MAXQ2);
  while (true) {
    int n;
    io::readInt(n);
    if (n < 0) {
      break;
    }
    int q;
    io::readInt(q);
    dis.resize(q << 1);
    us.resize(q);
    vs.resize(q);
    parities.resize(q);
    int idx = 0;
    FOR(i, 0, q) {
      io::readInt(us[i]);
      io::readInt(vs[i]);
      io::readCharArray(state);
      dis[idx++] = --us[i];
      dis[idx++] = vs[i];
      parities[i] = state[0] == 'o';
    }
    SORTUNIQUE(dis);
    dset.init(SIZE(dis));
    for (idx = 0; idx < q; ++idx) {
      int u = INDEX(dis, us[idx]);
      int v = INDEX(dis, vs[idx]);
      bool valid;
      dset.unionSet(u, v, parities[idx], valid);
      if (!valid) {
        break;
      }
    }
    io::writeInt(idx);
    io::writeChar('\n');
  }
}
