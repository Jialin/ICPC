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
#define FILL(vs,v) fill(ALL(vs), v)
#define CLEAR(q) for (;!q.empty();q.pop())
#define UNIQUE(v) sort(ALL(v));(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) (CAST<int>(lower_bound(ALL(v),x)-BEGIN(v)))
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

const int VASE = 20;
const int PLAYER = 100;
const int WINNING_VASE = 6;
const int LOSING_VASE = 20 - WINNING_VASE;
const int ROUND = 6;

inline int getDay() {
  int res; scanf("%d", &res);
  return res;
}

inline int getVase(int vaseIdx) {
  printf("%d 0\n", vaseIdx + 1); FLUSH;
  int res; scanf("%d", &res);
  FOR(i, 0, res) {
    int tmp; scanf("%d", &tmp);
  }
  return res;
}

int main() {
  assert(LOSING_VASE * ROUND + WINNING_VASE < PLAYER);
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int day = 1;
    FOR(_, 0, ROUND) {
      FOR(vaseIdx, WINNING_VASE, VASE) {
        assert(day == getDay());
        printf("%d 1\n", vaseIdx + 1); FLUSH;
        ++day;
      }
    }
    vector<pair<int, int>> sizes;
    FOR(vaseIdx, 0, WINNING_VASE) {
      assert(day == getDay());
      sizes.push_back(make_pair(getVase(vaseIdx), vaseIdx));
      ++day;
    }
    sort(ALL(sizes));
    for (int i = 1; i < SIZE(sizes); ++i) {
      for (int j = sizes[i].first; j < sizes[0].first + 2; ++j) {
        assert(day == getDay());
        printf("%d 1\n", sizes[i].second + 1); FLUSH;
        ++day;
      }
    }
    while (day < PLAYER) {
      for (int i = 1; i < SIZE(sizes) && day < PLAYER; ++i) {
        assert(day == getDay());
        printf("%d 1\n", sizes[i].second + 1); FLUSH;
        ++day;
      }
    }
    assert(PLAYER == getDay());
    printf("%d 100\n", sizes[0].second + 1); FLUSH;
  }
  return 0;
}
