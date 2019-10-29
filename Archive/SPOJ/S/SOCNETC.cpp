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

namespace cs {

class DisjointSet {
public:
  vector<int> p;

  inline void init(int n) {
    p.resize(n);
    fill(p.begin(), p.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p[root] >= 0; root = p[root]) {}
    while (p[x] >= 0) {
      int tmp = p[x];
      p[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      p[rootX] += p[rootY];
      p[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcSize(int x) {
    return -p[calcRoot(x)];
  }
}; // class DisjointSet
} // namespace cs

char op[2];
cs::DisjointSet dset;

int main() {
  int n, m; scanf("%d%d", &n, &m);
  dset.init(n);
  int q; scanf("%d", &q);
  FOR(_, 0, q) {
    int x; scanf("%s%d", op, &x); --x;
    if (op[0] == 'S') {
      printf("%d\n", dset.calcSize(x));
    } else {
      int y; scanf("%d", &y); --y;
      if (op[0] == 'A') {
        int rootX = dset.calcRoot(x);
        int rootY = dset.calcRoot(y);
        if (rootX != rootY && -dset.p[rootX] - dset.p[rootY] <= m) {
          dset.p[rootX] += dset.p[rootY];
          dset.p[rootY] = rootX;
        }
      } else {
        puts(dset.isFriend(x, y) ? "Yes" : "No");
      }
    }
  }
  return 0;
}
