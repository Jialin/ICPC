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

namespace math {

inline int slightFix(int a, int mod) {
  return a >= mod
      ? a - mod
      : a < 0 ? a + mod : a;
}

inline int fix(int a, int mod) {
  a = slightFix(a, mod);
  return 0 <= a && a < mod ? a : slightFix(a % mod, mod);
}

inline int add(int a, int b, int mod) {
  return fix(a + b, mod);
}

inline int sub(int a, int b, int mod) {
  return fix(a - b, mod);
}

class ModInt {
public:
  inline ModInt(int mod = 1000000007) : mod_(mod) {}

  inline int add(int a, int b) { return math::add(a, b, mod_); }
  inline int sub(int a, int b) { return math::sub(a, b, mod_); }
private:
  int mod_;
}; // class ModUtils
} // namespace math

const int MAXM = 1 << 10;

int n, m;
vector<int> as, bs;
vector<int> cnts, nxtCnts;
math::ModInt mod(100000007);

inline int calc(int mask) {
  fill(cnts.begin(), cnts.end(), 0); cnts[0] = 1;
  for (int a : as) {
    fill(nxtCnts.begin(), nxtCnts.end(), 0);
    FOR(i, 0, mask) {
      int j = i ^ a;
      nxtCnts[j] = mod.add(nxtCnts[j], cnts[i]);
    }
    FOR(i, 0, mask) {
      nxtCnts[i] = mod.add(nxtCnts[i], cnts[i]);
    }
    cnts.swap(nxtCnts);
  }
  int res = 0;
  FOR(i, 0, mask) res = mod.add(res, cnts[i]);
  for (int b : bs) if (b < mask) {
    res = mod.sub(res, cnts[b]);
  }
  return res;
}

int main() {
  cnts.resize(MAXM);
  nxtCnts.resize(MAXM);
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    as.resize(n);
    int mask = 1;
    FOR(i, 0, n) {
      int v; scanf("%d", &v);
      as[i] = v;
      if (v) {
        mask = max(mask, 1 << (31 - __builtin_clz(v)));
      }
    }
    bs.resize(m); FOR(i, 0, m) scanf("%d", &bs[i]);
    printf("Case %d: %d\n", taskIdx, calc(mask << 1));
  }
  return 0;
}
