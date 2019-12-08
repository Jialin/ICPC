#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

#define FOR(i, a, b) for (int i = a; i < b; ++i)

#define CAST static_cast
#define SIZE(vs) static_cast<int>(vs.size())

namespace collections {

namespace {
template <typename T, typename CMP_T>
bool cmpFraction(T num1, T den1, T num2, T den2) {
  if (den1 < 0) {
    num1 = -num1;
    den1 = -den1;
  }
  if (den2 < 0) {
    num2 = -num2;
    den2 = -den2;
  }
  return CAST<CMP_T>(num1) * den2 < CAST<CMP_T>(num2) * den1;
}
} // namespace

template <typename T = int, typename CMP_T = long long>
class ConvexHullTricksIntInMonoAdd {
public:
  inline void init(bool calcMax) { calcMax_ = calcMax; }

  inline void add(T a, T b) {
    if (as_.empty()) {
      as_.push_back(a);
      bs_.push_back(b);
      return;
    }
    bool addFront =
        (calcMax_ && a <= as_.front()) || (!calcMax_ && a >= as_.front());
    if (topA_(addFront) == a) {
      if ((calcMax_ && b <= topB_(addFront)) ||
          (!calcMax_ && b >= topB_(addFront))) {
        return;
      }
      pop_(addFront);
    }
    T num, den;
    while (true) {
      num = b - topB_(addFront);
      den = topA_(addFront) - a;
      if (nums_.empty() ||
          (addFront &&
           cmpFraction<T, CMP_T>(num, den, nums_.front(), dens_.front())) ||
          (!addFront &&
           cmpFraction<T, CMP_T>(nums_.back(), dens_.back(), num, den))) {
        break;
      }
      pop_(addFront);
    }
    add_(addFront, a, b, num, den);
  }

  inline int queryLineIdx(T x) {
    if (nums_.empty() ||
        !cmpFraction<T, CMP_T>(nums_.front(), dens_.front(), x, CAST<T>(1))) {
      return 0;
    }
    int res = 0;
    for (int lower = 1, upper = SIZE(nums_); lower < upper;) {
      int medium = (lower + upper) >> 1;
      if (cmpFraction<T, CMP_T>(nums_[medium], dens_[medium], x, CAST<T>(1))) {
        res = medium;
        lower = medium + 1;
      } else {
        upper = medium;
      }
    }
    return res + 1;
  }

  inline T query(T x) {
    int idx = queryLineIdx(x);
    return as_[idx] * x + bs_[idx];
  }

  inline void popFront() {
    as_.pop_front();
    bs_.pop_front();
    if (!nums_.empty()) {
      nums_.pop_front();
      dens_.pop_front();
    }
  }

  inline void popBack() {
    as_.pop_back();
    bs_.pop_back();
    if (!nums_.empty()) {
      nums_.pop_back();
      dens_.pop_back();
    }
  }

  inline T frontA() { return as_.front(); }

  inline T backA() { return as_.back(); }

private:
  inline T topA_(bool addFront) { return addFront ? frontA() : backA(); }

  inline T topB_(bool addFront) { return addFront ? bs_.front() : bs_.back(); }

  inline void pop_(bool addFront) {
    if (addFront) {
      popFront();
    } else {
      popBack();
    }
  }

  // Whether to maintain max curve (maintain min curve otherwise)
  bool calcMax_;
  // y = ax + b
  deque<T> as_, bs_;
  // joints at x axis
  deque<T> nums_, dens_;
}; // class ConvexHullTricksIntInMonoAdd

} // namespace collections

bool addBorder(vector<pair<int, int>> &xs, int x, int idx) {
  for (; !xs.empty() && xs.back().first < x; xs.pop_back()) {
  }
  if (!xs.empty() && xs.back().first == x) {
    return false;
  }
  xs.emplace_back(x, idx);
  return true;
}

int n;
vector<pair<int, int>> xs;
vector<pair<int, int>> ys;

int main() {
  scanf("%d", &n);
  xs.reserve(n);
  ys.reserve(n);
  FOR(i, 0, n) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (!addBorder(xs, x, i) && !addBorder(ys, y, i)) {
      continue;
    }
  }
  return 0;
}
