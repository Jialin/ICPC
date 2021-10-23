// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "ds/sliding_window/max_sliding_window.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  ds::MaxSlidingWindow<int> sw;
  FOR(_, 0, q) {
    int ws;
    io::readInt(ws);
    sw.init(ws);
    FOR(i, 0, ws - 1) {
      sw.push_back(i, vs[i]);
    }
    int res = 1000000;
    FOR(i, ws - 1, n) {
      sw.push_back(i, vs[i]);
      res = min(res, sw.get().second);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
}
