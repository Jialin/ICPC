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

int n, m;
vector<int> xs, ys, disX, disY;
vector<char> ds;
vector<vector<int>> cnts;
char token[10];

void calc() {
  int r = SIZE(disX), c = SIZE(disY);
  cnts.resize(r);
  for (auto& cnt : cnts) {
    cnt.resize(c);
    fill(cnt.begin(), cnt.end(), 0);
  }
  FOR(i, 0, n) {
    switch (ds[i]) {
    case 'N':
      ++cnts[0][upper_bound(disY.begin(), disY.end(), ys[i]) - disY.begin()];
      break;
    case 'S':
      ++cnts[0][0];
      --cnts[0][lower_bound(disY.begin(), disY.end(), ys[i]) - disY.begin()];
      break;
    case 'E':
      ++cnts[upper_bound(disX.begin(), disX.end(), xs[i]) - disX.begin()][0];
      break;
    case 'W':
      ++cnts[0][0];
      --cnts[lower_bound(disX.begin(), disX.end(), xs[i]) - disX.begin()][0];
      break;
    }
  }
  FOR(i, 1, r) cnts[i][0] += cnts[i - 1][0];
  FOR(j, 1, c) cnts[0][j] += cnts[0][j - 1];
  FOR(i, 1, r) FOR(j, 1, c) cnts[i][j] += cnts[i][j - 1] + cnts[i - 1][j] - cnts[i - 1][j - 1];
  int res = 0;
  FOR(i, 0, r) FOR(j, 0, c) res = max(res, cnts[i][j]);
  FOR(i, 0, r) FOR(j, 0, c) if (res == cnts[i][j]) {
    printf("%d %d\n", disX[i], disY[j]);
    return;
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    xs.resize(n);
    ys.resize(n);
    ds.resize(n);
    disX.clear(); disX.push_back(0); disX.push_back(m);
    disY.clear(); disY.push_back(0); disY.push_back(m);
    FOR(i, 0, n) {
      int x, y; scanf("%d%d%s", &x, &y, token);
      xs[i] = x;
      ys[i] = y;
      ds[i] = token[0];
      switch (ds[i]) {
      case 'N':
        disY.push_back(y + 1);
        break;
      case 'S':
        disY.push_back(y - 1);
        break;
      case 'E':
        disX.push_back(x + 1);
        break;
      case 'W':
        disX.push_back(x - 1);
        break;
      }
    }
    UNIQUE(disX);
    UNIQUE(disY);
    printf("Case #%d: ", taskIdx);
    calc();
  }
  return 0;
}
