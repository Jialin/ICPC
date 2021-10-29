// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

inline int calc(int n, int k, const vector<int>& vs) {
  if (k > 2) {
    return *max_element(ALL(vs));
  }
  if (k == 1) {
    return *min_element(ALL(vs));
  }
  vector<int> minVs(n);
  minVs[0] = vs[0];
  FOR(i, 1, n) {
    minVs[i] = min(minVs[i - 1], vs[i]);
  }
  int rightMin = vs[n - 1];
  int res = max(minVs[n - 2], rightMin);
  for (int i = n - 2; i > 0; --i) {
    rightMin = min(rightMin, vs[i]);
    res = max(res, max(minVs[i - 1], rightMin));
  }
  return res;
}

int main() {
  int n, k;
  io::readInt(n);
  io::readInt(k);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  io::writeInt(calc(n, k, vs));
  io::writeChar('\n');
}
