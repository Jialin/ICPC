#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v), END(v)

#define FOR(i, l, r) for (int i = (l); i < (r); ++i)

namespace mu {

// Checks whether the number is in the form of 2^x
inline bool isPow2(int n) {
  return n && !(n & (n - 1));
}

// Computes the smallest 2^x which is not less than n.
inline int nextPow2(int n) {
  if (n <= 1) return 1;
  return isPow2(n) ? n : 1 << (32 - __builtin_clz(static_cast<unsigned int>(n)));
}

} // namespace mu

namespace cs { namespace bit {

template <typename T>
class BinaryIndexedTree {
  int n;
  vector<T> vs;

  inline static int transform(int i) {
    return (i & (i + 1)) - 1;
  }

public:
  inline void init(int n_, bool fixed = true) {
    this->n = n_;
    vs.reserve(fixed ? n : mu::nextPow2(n));
    vs.resize(n);
    fill(ALL(vs), 0);
  }

  inline void update(int i, const T &delta) {
    for (; i < n; i |= i + 1) {
      vs[i] += delta;
    }
  }

  inline T calc(int i) {
    if (i < 0) return T();
    T res = vs[i];
    for (i = transform(i); i >= 0; i = transform(i)) {
      res += vs[i];
    }
    return res;
  }

  inline T calcRange(int i, int j) {
    return calc(j) - calc(i - 1);
  }
};
}} // namespace cs::bit

using PII = pair<int, int>;

const int MAXN = 30000;
const int MAXQ = 200000;

int aCnt, as[MAXN], aOrder[MAXN];
int qCnt, ls[MAXQ], rs[MAXQ], ks[MAXQ], qOrder[MAXQ];
cs::bit::BinaryIndexedTree<int> bit;
int answer[MAXQ];

int main() {
  scanf("%d", &aCnt);
  FOR(i, 0, aCnt) {
    scanf("%d", as + i);
    aOrder[i] = i;
  }
  sort(aOrder, aOrder + aCnt, [](int x, int y) { return as[x] > as[y]; });
  scanf("%d", &qCnt);
  FOR(i, 0, qCnt) {
    scanf("%d%d%d", ls + i, rs + i, ks + i);
    --ls[i];
    --rs[i];
    qOrder[i] = i;
  }
  sort(qOrder, qOrder + qCnt, [](int x, int y) { return ks[x] > ks[y]; });
  bit.init(aCnt);
  int pnt = 0;
  FOR(i, 0, qCnt) {
    int qIdx = qOrder[i];
    for (int aIdx = aOrder[pnt]; pnt < aCnt && as[aIdx] > ks[qOrder[i]];
         aIdx = aOrder[++pnt]) {
      bit.update(aIdx, 1);
    }
    answer[qIdx] = bit.calcRange(ls[qIdx], rs[qIdx]);
  }
  FOR(i, 0, qCnt) printf("%d\n", answer[i]);
  return 0;
}
