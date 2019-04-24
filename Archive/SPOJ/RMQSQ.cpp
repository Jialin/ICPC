#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace cs { namespace rmq {

template<typename T>
class RMQ {
  int n;
  T* vs;
  vector<vector<int>> rmqIdx;

  static inline int highestBit(int n) {
    return 31 - __builtin_clz(n);
  }

  inline void _init() {
    int bit = highestBit(n);
    rmqIdx.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx[i].resize(n - (1 << i) + 1);
    for (int i = 0; i < n; ++i) rmqIdx[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx[i - 1][j];
      int kIdx = rmqIdx[i - 1][k];
      rmqIdx[i][j] = vs[jIdx] < vs[kIdx] ? jIdx : kIdx;
    }
  }
public:
  inline void init(int _n, T* _vs) {
    n = _n;
    vs = _vs;
    _init();
  }

  inline int calcMinIndex(int lower, int upper) {
    int bit = highestBit(upper - lower + 1);
    int lowerIdx = rmqIdx[bit][lower];
    int upperIdx = rmqIdx[bit][upper - (1 << bit) + 1];
    return vs[lowerIdx] < vs[upperIdx] ? lowerIdx : upperIdx;
  }

  inline T& calcMin(int lower, int upper) {
    return vs[calcMinIndex(lower, upper)];
  }
}; // class RMQ
}} // namespace cs::rmq

const int MAXN = 100000;

int a[MAXN];
cs::rmq::RMQ<int> rmq;

int main() {
  int n; scanf("%d", &n);
  FOR(i, 0, n) scanf("%d", a + i);
  rmq.init(n, a);
  int q; scanf("%d", &q);
  FOR(i, 0, q) {
    int lower, upper; scanf("%d%d", &lower, &upper);
    printf("%d\n", rmq.calcMin(lower, upper));
  }
  return 0;
}
