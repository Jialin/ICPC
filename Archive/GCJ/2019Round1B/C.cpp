#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define CAST static_cast
#define SIZE(v) (CAST<int>((v).size()))
#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace cs {

template<typename T, typename Compare = less<T>>
class RMQ {
public:
  inline RMQ(): cmp_(Compare()) {}

  inline void init(int n, T* vs) {
    n_ = n;
    vs_ = vs;
    init_();
  }

  inline void init(vector<T>& vs) {
    init(SIZE(vs), vs.data());
  }

  inline int calcIdx(int lower, int upper) const {
    int bit = highestBit_(upper - lower);
    int lowerIdx = rmqIdx_[bit][lower];
    int upperIdx = rmqIdx_[bit][upper - (1 << bit)];
    return cmp_(vs_[lowerIdx], vs_[upperIdx]) ? lowerIdx : upperIdx;
  }

  inline T& calc(int lower, int upper) {
    return vs_[calcIdx(lower, upper)];
  }

  inline int n() const { return n_; }

private:
  const Compare cmp_;
  int n_;
  T* vs_;
  vector<vector<int>> rmqIdx_;

  inline static int highestBit_(int n) { return 31 - __builtin_clz(n); }

  inline void init_() {
    int bit = highestBit_(n_);
    rmqIdx_.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx_[i].resize(n_ - (1 << i) + 1);
    for (int i = 0; i < n_; ++i) rmqIdx_[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n_ - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx_[i - 1][j];
      int kIdx = rmqIdx_[i - 1][k];
      rmqIdx_[i][j] = cmp_(vs_[jIdx], vs_[kIdx]) ? jIdx : kIdx;
    }
  }
}; // class RMQ
} // namespace cs

int n, K;
vector<int> as, bs;
cs::RMQ<int, greater<int>> rmqA, rmqB;

LL calcInvalid(int x, int leftMax, int rightMax) {
  int lower, upper;
  // left
  int leftSize = 0;
  lower = 1;
  upper = leftMax;
  while (lower <= upper) {
    int medium = (lower + upper) >> 1;
    if (rmqB.calc(x - medium, x) < as[x] - K) {
      leftSize = medium;
      lower = medium + 1;
    } else {
      upper = medium - 1;
    }
  }
  // right
  int rightSize = 0;
  lower = 1;
  upper = rightMax;
  while (lower <= upper) {
    int medium = (lower + upper) >> 1;
    if (rmqB.calc(x + 1, x + medium + 1) < as[x] - K) {
      rightSize = medium;
      lower = medium + 1;
    } else {
      upper = medium - 1;
    }
  }
  return (leftSize + 1LL) * (rightSize + 1);
}

LL calc(int x) {
  int lower, upper;
  // left
  int leftSize = 0;
  lower = 1;
  upper = x;
  while (lower <= upper) {
    int medium = (lower + upper) >> 1;
    if (rmqA.calc(x - medium, x) <= as[x] && rmqB.calc(x - medium, x) <= as[x] + K) {
      leftSize = medium;
      lower = medium + 1;
    } else {
      upper = medium - 1;
    }
  }
  // right
  int rightSize = 0;
  lower = 1;
  upper = n - 1 - x;
  while (lower <= upper) {
    int medium = (lower + upper) >> 1;
    if (rmqA.calc(x + 1, x + medium + 1) < as[x] && rmqB.calc(x + 1, x + medium + 1) <= as[x] + K) {
      rightSize = medium;
      lower = medium + 1;
    } else {
      upper = medium - 1;
    }
  }
  LL res = (leftSize + 1LL) * (rightSize + 1);
  if (as[x] - K > bs[x]) res -= calcInvalid(x, leftSize, rightSize);
  return res;
}

LL calc() {
  LL res = 0;
  FOR(i, 0, n) if (as[i] + K >= bs[i]) {
    res += calc(i);
  }
  return res;
}


int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &K);
    as.resize(n);
    bs.resize(n);
    FOR(i, 0, n) scanf("%d", &as[i]);
    FOR(i, 0, n) scanf("%d", &bs[i]);
    rmqA.init(as);
    rmqB.init(bs);
    printf("Case #%d: %lld\n", taskIdx, calc());
  }
  return 0;
}
