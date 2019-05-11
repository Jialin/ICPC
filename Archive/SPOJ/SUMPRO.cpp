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

namespace math {

inline void stepIterate(int n, function<void(int, int, int)> processor) {
  int lastX = n;
  for (int y = 1; y <= n / y; ++y) {
    int x = n / (y + 1);
    processor(x + 1, lastX, y);
    lastX = x;
  }
  for (int x = lastX; x > 0; --x) {
    processor(x, x, n / x);
  }
}
} // namespace math

int calc(int n) {
  LL res = 0;
  math::stepIterate(n, [&res](int xLower, int xUpper, int y) {
    if (xLower == xUpper) {
      res += xLower * y;
    } else {
      res += (((xLower + xUpper) * (xUpper - xLower + 1LL)) >> 1) * y;
    }
  });
  return CAST<int>(res % 1000000007);
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    printf("%d\n", calc(n));
  }
  return 0;
}
