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

#define SIZE(v) (static_cast<int>((v).size()))

namespace ss { namespace utils {

inline string toString(const vector<int>& vs) {
  ostringstream ss;
  ss << '[';
  bool first = true;
  for (auto v : vs) {
    if (first) {
      first = false;
    } else {
      ss << ' ';
    }
    ss << v;
  }
  ss << ']';
  return ss.str();
}

}} // namespace ss::utils

namespace ss { namespace kmp {

template<typename T = char>
class KMP {
  int n;
  const T* pattern;
  vector<int> fail;

public:
  inline int calcNextPosition(int pos, T c) const {
    for (pos = pos == n - 1 ? fail[pos] : pos; pos >= 0 && pattern[pos + 1] != c; pos = fail[pos]) {}
    return pattern[pos + 1] == c ? pos + 1 : -1;
  }

  // Initializes fail
  inline void init(int _n, const T* _pattern) {
    this->n = _n;
    this->pattern = _pattern;
    fail.resize(n);
    fail[0] = -1;
    for (int i = 1; i < n; ++i) {
      fail[i] = calcNextPosition(fail[i - 1], pattern[i]);
    }
  }

  // Finds all occurence of matching patterns
  inline void findAll(int m, const T* s, vector<int>& matchStartPositions) {
    int pos = -1;
    for (int i = 0; i < m; ++i) {
      pos = calcNextPosition(pos, s[i]);
      if (pos == n - 1) matchStartPositions.push_back(i - n + 1);
    }
  }
};
}} // namespace ss::kmp

const int MAXL = 1000000 + 1;

int n, m;
char pattern[MAXL], s[MAXL];
vector<int> res;
ss::kmp::KMP<> kmp;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    if (taskIdx > 1) putchar('\n');
    scanf("%s", s); n = static_cast<int>(strlen(s));
    scanf("%s", pattern); m = static_cast<int>(strlen(pattern));
    kmp.init(m, pattern);
    res.clear();
    kmp.findAll(n, s, res);
    if (res.empty()) {
      puts("Not Found");
    } else {
      printf("%d\n%d", SIZE(res), res[0] + 1);
      for (int i = 1; i < SIZE(res); ++i) {
        printf(" %d", res[i] + 1);
      }
      putchar('\n');
    }
  }
  return 0;
}
