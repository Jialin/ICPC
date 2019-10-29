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

template<typename T, typename Compare = less<T>>
class LIS {
public:
  inline void init(int n) {
    lis_.clear();
    lis_.reserve(n);
    result_ = 0;
  }

  inline int locateIdx(const T& v) const {
    return CAST<int>(lower_bound(lis_.begin(), lis_.end(), v, cmp_) - lis_.begin());
  }

  inline void add(const T& v) {
    int idx = locateIdx(v);
    if (idx == SIZE(lis_)) {
      lis_.push_back(v);
    } else {
      lis_[idx] = v;
    }
  }

  inline int length() const { return SIZE(lis_); }

private:
  vector<T> lis_;
  int result_;
  Compare cmp_;
}; // class LIS
} // namespace cs

const int MAXN = 1000;

int n, m;
int a[MAXN];
cs::LIS<int, greater<int>> lis;

inline int calcNoJump() {
  lis.init(n);
  FOR(i, 0, n) lis.add(a[i]);
  return lis.length();
}

inline int calcJump() {
  lis.init(m + 1);
  FOR(i, 0, m + 1) lis.add(a[i]);
  int res = lis.locateIdx(a[m]) + 1;
  lis.init(n - m - 1);
  FOR(i, m + 1, n) lis.add(a[i]);
  return res + lis.length();
}

inline int calc() {
  return max(calcNoJump(), calcJump());
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    FOR(i, 0, n) scanf("%d", a + i);
    printf("%d\n", calc());
  }
  return 0;
}
