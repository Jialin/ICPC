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

/** TO BE VERIFIED. */
namespace cs { namespace bit {

template <typename T>
class BinaryIndexedTree {
  int n;
  vector<T> vs;

  inline static int transform(int i) {
    return (i & (i + 1)) - 1;
  }

public:
  // Initializes
  inline void init(int _n) {
    this->n = _n;
    vs.resize(n);
    fill(vs.begin(), vs.end(), 0);
  }

  // Adds delta @ position i
  inline void update(int i, const T &delta) {
    for (; i < n; i |= i + 1) {
      vs[i] += delta;
    }
  }

  // Calculates sum from position 0 to position i
  inline T calc(int i) {
    if (i < 0) return T();
    T res = vs[i];
    for (i = transform(i); i >= 0; i = transform(i)) {
      res += vs[i];
    }
    return res;
  }

  // Calculates sum from position i to position j
  inline T calcRange(int i, int j) {
    return calc(j) - calc(i - 1);
  }
}; // class BinaryIndexedTree
}} // namespace cs::bit

cs::bit::BinaryIndexedTree<int> bit;
char op[5];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  bit.init(n);
  FOR(i, 0, q) {
    int x, y;
    scanf("%s%d%d", op, &x, &y); --x;
    if (op[0] == 'a') {
      bit.update(x, y);
    } else {
      printf("%d\n", bit.calcRange(x, y - 1));
    }
  }
  return 0;
}
