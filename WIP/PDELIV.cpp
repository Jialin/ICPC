#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

namespace collections {

class IntervalTreeRangeQueryBase {
  int n;
  vector<int> lowers, uppers;

  virtual inline void initNodes(int n) = 0;
  virtual inline void initLeafNode(const INIT_V &initValue) = 0;
  virtual inline void merge(int idx, int leftIdx, int rightIdx) = 0;

public:
  inline void
  initLeafsAndMerge(int n_, function<void(int nodeIdx, int idx)> &initializer) {
    n = n_;
    int n2 = n << 1;
    lowers.assign(n2, n);
    uppers.assign(n2, -1);
    initNodes(n2);
    for (int i = 0, j = n; i < n; ++i, ++j) {
      lowers[j] = i;
      uppers[j] = i + 1;
      initializer(j, i);
    }
    for (int i = n - 1, leftIdx = i << 1, rightIdx = leftIdx | 1; i >= 0;
         --i, leftIdx -= 2, rightIdx -= 2) {
      if (uppers[rightIdx] == lowers[leftIdx]) {
        lowers[i] = lowers[leftIdx];
        uppers[i] = uppers[rightIdx];
        merge(i, leftIdx, rightIdx);
      }
    }
  }

  inline void query(int lower, int upper,
                    const function<void(int nodeIdx)> &queryProcessor) {
    for (lower += n, upper += n; lower < upper; lower >>= 1, upper >>= 1) {
      if (lower & 1) {
        if (isValid(lower)) {
          queryProcessor(lower);
        }
        ++lower;
      }
      if ((upper & 1) && isValid(--upper)) {
        queryProcessor(upper);
      }
    }
  }
};

} // namespace collections

int main() {
  scanf("%s");
  p();
  return 0;
}
