#pragma once

#include <vector>

using namespace std;

namespace collections {

class UniqueCounter {
public:
  inline UniqueCounter(int n, int capacity = -1) {
    init(n, capacity);
  }

  inline void init(int n, int capacity = -1) {
    zeroCnt = n;
    nonZeroCnt = 0;
    if (capacity >= 0) {
      cnts.reserve(capacity);
    }
    cnts.assign(n, 0);
  }

  inline void update(int x, int v) {
    if (!v) {
      return;
    }
    if (!cnts[x]) {
      --zeroCnt;
      ++nonZeroCnt;
    }
    cnts[x] += v;
    if (!cnts[x]) {
      ++zeroCnt;
      --nonZeroCnt;
    }
  }

  int zeroCnt, nonZeroCnt;
  vector<int> cnts;
};

} // namespace collections
