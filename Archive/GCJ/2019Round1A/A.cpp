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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define SIZE(v) (static_cast<int>((v).size()))

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)

#define FOR(i,l,r) for(int i=(l);i<(r);++i)
#define FOREACH(i,v) for(typeof((v).begin()) i=(v).begin();i!=(v).end();++i)

namespace gs {
class UnweightedSimpleGraph {
public:
  int n;
  vector<vector<bool>> adj;
  vector<int> outDegree;

  inline void init(int _n) {
    n = _n;
    adj.resize(n);
    for (auto& v : adj) {
      v.resize(n);
      fill(v.begin(), v.end(), false);
    }
    outDegree.resize(n);
    fill(outDegree.begin(), outDegree.end(), 0);
  }

  inline void addDirected(int x, int y) {
    if (!adj[x][y]) {
      adj[x][y] = true;
      ++outDegree[x];
    }
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }
}; // namespace UnweightedSimpleGraph
} // namespace gs

namespace gs {

namespace {
  inline static bool isCycle(const gs::UnweightedSimpleGraph& g, const vector<int>& cycle) {
    for (int i = 0, j = 1; i < g.n; ++i) {
      if (!g.adj[cycle[i]][cycle[j]]) return false;
      ++j; if (j == g.n) j = 0;
    }
    return true;
  }
} // namespace

// Ore's Theorem
class Ore {
public:
  // Whether the graph satistifies all conditions in Ore's theorem
  inline static bool isValid(const gs::UnweightedSimpleGraph& g) {
    if (g.n < 3) return false;
    for (int i = 0; i < g.n; ++i) for (int j = i + 1; j < g.n; ++j) {
      if (!g.adj[i][j] && g.outDegree[i] + g.outDegree[j] < g.n) return false;
    }
    return true;
  }

  // Constructs a Hamiltonian cycle
  inline static void construct(const gs::UnweightedSimpleGraph& g, vector<int>& cycle) {
    cycle.resize(g.n);
    for (int i = 0; i < g.n; ++i) cycle[i] = i;
    while (!isCycle(g, cycle)) {
      for (int i = 0; i < g.n; ++i) {
        int i1 = i == g.n - 1 ? 0 : i + 1;
        if (g.adj[cycle[i]][cycle[i1]]) continue;
        for (int j = 0; j < g.n; ++j) {
          int j1 = j == g.n - 1 ? 0 : j + 1;
          if (i == j || i == j1 || i1 == j || i1 == j1) continue;
          if (!g.adj[cycle[i]][cycle[j]] || !g.adj[cycle[i1]][j1]) continue;
          if (i1 < j) {
            reverse(cycle.begin() + i1, cycle.begin() + j + 1);
          } else {
            reverse(cycle.begin() + j1, cycle.begin() + i + 1);
          }
        }
      }
    }
  }
}; // class Ore
} // namespace gs

const int DFS_LIMIT = 10000000;
const int ATTEMPT = 10;
const int MAXN = 20;

int n, m, nm;
gs::UnweightedSimpleGraph g;
vector<int> cycle;
unordered_set<int> xSet, ySet;
vector<int> xRes, yRes;
int dfsCnt;
bool found;
bool used[MAXN][MAXN];

bool isValid(int x, int y) {
  if (xRes.empty()) return true;
  int xx = xRes.back();
  int yy = yRes.back();
  return x != xx
      && y != yy
      && x + y != xx + yy
      && x - y != xx - yy;
}

void dfs(int depth) {
  if (depth == nm) {
    found = true;
    return;
  }
  ++dfsCnt;
  if (dfsCnt >= DFS_LIMIT) return;
  bool xFill = xSet.empty();
  bool yFill = ySet.empty();
  if (xFill) FOR(i, 0, n) xSet.insert(i);
  if (yFill) FOR(j, 0, m) ySet.insert(j);
  vector<pair<int, int>> xys;
  for (auto x : xSet) for (auto y : ySet) if (!used[x][y] && isValid(x, y)) xys.emplace_back(x, y);
  random_shuffle(xys.begin(), xys.end());
  for (int round = min(ATTEMPT, SIZE(xys)) - 1; round >= 0; --round) {
    int x = xys[round].first;
    int y = xys[round].second;
    used[x][y] = true;
    xSet.erase(x);
    ySet.erase(y);
    xRes.push_back(x);
    yRes.push_back(y);
    dfs(depth + 1);
    if (found || dfsCnt >= DFS_LIMIT) return;
    used[x][y] = false;
    xSet.insert(x);
    ySet.insert(y);
    xRes.pop_back();
    yRes.pop_back();
  }
  if (xFill) xSet.clear();
  if (yFill) ySet.clear();
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    printf("Case #%d: ", taskIdx);
    nm = n * m;
    g.init(nm);
    FOR(i, 0, nm) FOR(j, 0, nm) {
      int x0 = i / m, y0 = i % m;
      int x1 = j / m, y1 = j % m;
      if (x0 == x1 || y0 == y1 || x0 - y0 == x1 - y1 || x0 + y0 == x1 + y1) continue;
      g.addUndirected(i, j);
    }
    if (gs::Ore::isValid(g)) {
      gs::Ore::construct(g, cycle);
      puts("POSSIBLE");
      for (int xy : cycle) printf("%d %d\n", xy / m + 1, xy % m + 1);
      continue;
    }
    // fall back
    xSet.clear();
    ySet.clear();
    xRes.clear();
    yRes.clear();
    found = false;
    dfsCnt = 0;
    memset(used, 0, sizeof(used));
    dfs(0);
    puts(found ? "POSSIBLE" : "IMPOSSIBLE");
    if (found) FOR(i, 0, nm) printf("%d %d\n", xRes[i] + 1, yRes[i] + 1);
  }
  return 0;
}
