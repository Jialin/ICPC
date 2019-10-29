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

/**
 * Code attached for convenience.
 */
namespace mu {

// Checks whether the number is in the form of 2^x
inline bool isPow2(int n) {
  return n && !(n & (n - 1));
}

// Computes the smallest 2^x which is not less than n.
inline int nextPow2(int n) {
  if (n <= 1) return 1;
  return isPow2(n) ? n : 1 << (32 - __builtin_clz(static_cast<unsigned int>(n)));
}
} // namespace mu

namespace cs { namespace lis {

template<typename T>
class LongestIncreasingSubsequence {
  vector<T> lis;

public:
  // Length of lis
  int length;

  // Initializes
  inline void init(int n, bool fixed = true) {
    lis.reserve(fixed ? n : mu::nextPow2(n));
    lis.resize(n);
    length = 0;
  }

  // Try to add v to lis
  inline void add(const T& v) {
    T absv = abs(v);
    const auto& lisBegin = lis.begin();
    long idx = lower_bound(lisBegin, lisBegin + length, absv) - lisBegin;
    if ((v > 0) ^ ((idx & 1) > 0)) {
      lis[idx] = absv;
      if (idx == length) ++length;
    }
  }
};
}} // namespace cs::lis

const int MAXN = 5000;

int aCnt, as[MAXN];
cs::lis::LongestIncreasingSubsequence<int> lis;

int calc() {
  lis.init(aCnt);
  FOR(i, 0, aCnt) lis.add(as[i]);
  return lis.length;
}

int main() {
  scanf("%d", &aCnt);
  FOR(i, 0, aCnt) scanf("%d", &as[i]);
  int res = calc();
  FOR(i, 0, aCnt) as[i] = -as[i];
  res = max(res, calc());
  printf("%d\n", res);
  return 0;
}
