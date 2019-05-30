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
#include <utility>
#include <vector>
using namespace std;

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

vector<int> lc;
deque<int> rc;

inline void balance() {
  if (lc.size() == rc.size()) return;
  lc.push_back(rc.front());
  rc.pop_front();
}

int main() {
  int v;
  while (scanf("%d", &v) != EOF) {
    if (!v) {
      lc.clear();
      rc.clear();
      puts("");
      continue;
    }
    if (v < 0) {
      printf("%d\n", lc.back());
      lc.pop_back();
    } else {
      rc.push_back(v);
    }
    balance();
  }
  return 0;
}
