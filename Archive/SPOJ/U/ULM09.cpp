#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
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
#include <tuple>
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

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

namespace cs {

class DisjointSet {
public:
  inline void init(int n) {
    p_.resize(n);
    fill(p_.begin(), p_.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p_[root] >= 0; root = p_[root]) {}
    while (p_[x] >= 0) {
      int tmp = p_[x];
      p_[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      if (p_[rootX] > p_[rootY]) swap(rootX, rootY);
      p_[rootX] += p_[rootY];
      p_[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcSize(int x) {
    return -p_[calcRoot(x)];
  }

private:
  vector<int> p_;
}; // class DisjointSet
} // namespace cs

int n, m;
vector<int> xs, ys, weights, orders;
cs::DisjointSet dset;

int main() {
  while (scanf("%d%d", &n, &m) != EOF && (n || m)) {
    xs.resize(m);
    ys.resize(m);
    weights.resize(m);
    orders.resize(m);
    int res = 0;
    FOR(i, 0, m) {
      scanf("%d%d%d", &xs[i], &ys[i], &weights[i]);
      orders[i] = i;
      res += weights[i];
    }
    sort(orders.begin(), orders.end(), [](int i, int j) {
      return weights[i] < weights[j];
    });
    dset.init(n);
    for (int i : orders) if (!dset.isFriend(xs[i], ys[i])) {
      res -= weights[i];
      dset.setFriend(xs[i], ys[i]);
    }
    printf("%d\n", res);
  }
  return 0;
}

