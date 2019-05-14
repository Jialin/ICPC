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

int n, m;
char board[16][16];
map<tuple<int, int, int, int>, int> sgF;
vector<bool> rs, cs;

int calc(int x1, int y1, int x2, int y2) {
  if (x1 >= x2 || y1 >= y2) return 0;
  auto t = make_tuple(x1, y1, x2, y2);
  if (sgF.count(t)) return sgF[t];
  fill(rs.begin() + x1, rs.begin() + x2, false);
  fill(cs.begin() + y1, cs.begin() + y2, false);
  FOR(i, x1, x2) FOR(j, y1, y2) if (board[i][j] == '#') {
    rs[i] = true;
    cs[j] = true;
  }
  vector<int> r; FOR(i, x1, x2) if (!rs[i]) r.push_back(i);
  vector<int> c; FOR(j, y1, y2) if (!cs[j]) c.push_back(j);
  set<int> sgS;
  for (int i : r) sgS.insert(calc(x1, y1, i, y2) ^ calc(i + 1, y1, x2, y2));
  for (int j : c) sgS.insert(calc(x1, y1, x2, j) ^ calc(x1, j + 1, x2, y2));
  for (int res = 0; ; ++res) if (!sgS.count(res)) {
    return sgF[t] = res;
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    FOR(i, 0, n) scanf("%s", board[i]);
    sgF.clear();
    rs.resize(n);
    cs.resize(m);
    int sg = calc(0, 0, n, m);
    printf("Case #%d: ", taskIdx);
    if (!sg) {
      puts("0");
      continue;
    }
    fill(rs.begin(), rs.end(), false);
    fill(cs.begin(), cs.end(), false);
    FOR(i, 0, n) FOR(j, 0, m) if (board[i][j] == '#') {
      rs[i] = true;
      cs[j] = true;
    }
    vector<int> r; FOR(i, 0, n) if (!rs[i]) r.push_back(i);
    vector<int> c; FOR(j, 0, m) if (!cs[j]) c.push_back(j);
    int resR = 0, resC = 0;
    for (int i : r) resR += calc(0, 0, i, m) == calc(i + 1, 0, n, m);
    for (int j : c) resC += calc(0, 0, n, j) == calc(0, j + 1, n, m);
    printf("%d\n", resR * m + resC * n);
  }
  return 0;
}
