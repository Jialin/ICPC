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

template<typename T>
class LIS {

public:
  vector<T> lis;
  // Length of lis
  int length;
  int n;

  // Initializes
  inline void init(int _n) {
    n = _n;
    lis.resize(n);
    length = 0;
  }

  // Try to add v to lis
  inline void add(const T& v) {
    T absv = abs(v);
    const auto& lisBegin = lis.begin();
    long idx = lower_bound(lisBegin, lisBegin + length, absv) - lisBegin;
//printf("n:%d idx:%ld lis.length=%ld\n", n, idx, lis.size());
    if (idx < n) lis[idx] = absv;
//puts("here2");
    if (idx == length && length < n) ++length;
//puts("here3");
  }
}; // class LIS
} // namespace cs

const int MAXN = 1000000;

int a[MAXN];
cs::LIS<int> lis;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    FOR(i, 0, n) scanf("%d", a + i);
    int m; scanf("%d", &m);
//printf("m:%d\n", m);
    lis.init(m);
    FOR(i, 0, n) lis.add(a[i]);
    printf("%d\n", lis.length == m ? lis.lis[m - 1] : -1);
  }
  return 0;
}
