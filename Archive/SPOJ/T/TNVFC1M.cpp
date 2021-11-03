// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_SLIDING_WINDOW_RESERVE
#include "ds/sliding_window/base_sliding_window_macros.h"

#include "ds/sliding_window/min_sliding_window.h"
#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 10000;

int main() {
  int n, h, lower, upper;
  vector<int> vs;
  vs.reserve(MAXN);
  vector<int> ress;
  ress.reserve(MAXN);
  ds::MinSlidingWindow<int> sw;
  sw.reserve(MAXN);
  while (io::readInt(n)) {
    io::readInt(h);
    io::readInt(lower);
    --lower;
    io::readInt(upper);
    vs.resize(n);
    FOR(i, 0, n) {
      io::readInt(vs[i]);
    }
    sw.init(h);
    FOR(i, max(lower - h, 0), lower) {
      sw.push_back(i, vs[i]);
    }
    ress.resize(n);
    fill(ress.begin() + lower, ress.begin() + upper, 0);
    int bound = min(upper + h, n);
    FOR(i, lower, bound) {
      sw.push_back(i, vs[i]);
      ++ress[sw.calc().first];
    }
    FOR(i, lower, upper) {
      io::writeInt(ress[i]);
      io::writeChar(i + 1 == upper ? '\n' : '\t');
    }
  }
  return 0;
}
