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
#define INDEX(v,x) (CAST<int>(lower_bound(ALL(v),x)-BEGIN(v)))
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

  inline bool isFriend(int x, int y) { return calcRoot(x) == calcRoot(y); }
  inline int calcSize(int x) { return -p_[calcRoot(x)]; }
  inline bool isRoot(int x) const { return p_[x] < 0; }
  inline int n() const { return SIZE(p_); }

private:
  vector<int> p_;
}; // class DisjointSet
} // namespace cs

int n, m;
vector<int> xs, ys;
vector<int> dis;
cs::DisjointSet dset;

int main() {
  scanf("%d%d", &n, &m);
  xs.reserve(m);
  ys.reserve(m);
  dis.reserve(m << 1);
  FOR(i, 0, m) {
    int x, y; scanf("%d%d", &x, &y);
    xs.push_back(x);
    ys.push_back(y);
    dis.push_back(x);
    dis.push_back(y);
  }
  UNIQUE(dis);
  dset.init(SIZE(dis));
  FOR(i, 0, m) {
    dset.setFriend(INDEX(dis, xs[i]), INDEX(dis, ys[i]));
  }
  int res = n;
  FOR(i, 0, SIZE(dis)) res -= !dset.isRoot(i);
  printf("%d\n", res);
  return 0;
}

