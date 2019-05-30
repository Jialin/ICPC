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

template<typename T>
class MediumContainer {
public:
  inline void init() {
    while (!lc_.empty()) lc_.pop();
    while (!rc_.empty()) rc_.pop();
  }

  inline void add(const T& v) {
    if (lc_.empty()) {
      lc_.push(v);
      return;
    }
    if (SIZE(lc_) == SIZE(rc_)) {
      const T& r = rc_.top();
      if (v <= r) {
        lc_.push(v);
      } else {
        lc_.push(r);
        rc_.pop();
        rc_.push(v);
      }
    } else {
      const T& l = lc_.top();
      if (l <= v) {
        rc_.push(v);
      } else {
        rc_.push(l);
        lc_.pop();
        lc_.push(v);
      }
    }
  }

  inline T popMedium() {
    T res = lc_.top();
    lc_.pop();
    if (SIZE(lc_) < SIZE(rc_)) {
      lc_.push(rc_.top());
      rc_.pop();
    }
    return res;
  }

  inline T medium() const { return lc_.top(); }

private:
  priority_queue<T> lc_;
  MINHEAP<T> rc_;
}; // class MediumContainer
} // namespace cs

cs::MediumContainer<int> container;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    container.init();
    int v;
    while (scanf("%d", &v) != EOF && v) {
      if (v < 0) {
        printf("%d\n", container.popMedium());
      } else {
        container.add(v);
      }
    }
  }
  return 0;
}

