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

const int MAXN = 100 + 1;
const int MAXC = 26;

void init(int n, char s[MAXN], int jump[MAXN][MAXN]) {
  FOR(i, 0, MAXC) jump[i][n - 1] = -1;
  jump[s[n - 1] - 'a'][n - 1] = n - 1;
  for (int i = n - 2; i >= 0; --i) {
    FOR(j, 0, MAXC) jump[j][i] = jump[j][i + 1];
    jump[s[i] - 'a'][i] = i;
  }
}

int n, m, K;
char s1[MAXN], s2[MAXN];
int jump1[MAXC][MAXN], jump2[MAXC][MAXN];
int dp[MAXN][MAXN], tag[MAXN][MAXN];
vector<int> qx, qy, qv;
vector<int> newQx, newQy, newQv;

int calc() {
  qx.clear(); qx.push_back(0);
  qy.clear(); qy.push_back(0);
  qv.clear(); qv.push_back(0);
  for (int loop = 0; loop < K; ++loop) {
    newQx.clear();
    newQy.clear();
    while (!qx.empty()) {
      int x = qx.back(); qx.pop_back();
      int y = qy.back(); qy.pop_back();
      int v = qv.back(); qv.pop_back();
      if (x >= n || y >= m) continue;
      FOR(i, 0, MAXC) {
        int newX = jump1[i][x] + 1;
        int newY = jump2[i][y] + 1;
        if (newX <= 0 || newY <= 0) continue;
        int newV = v + 'a' + i;
        if (tag[newX][newY] != loop || dp[newX][newY] < newV) {
          dp[newX][newY] = newV;
          if (tag[newX][newY] != loop) {
            tag[newX][newY] = loop;
            newQx.push_back(newX);
            newQy.push_back(newY);
          }
        }
      }
    }
    newQv.clear();
    FOR(i, 0, SIZE(newQx)) newQv.push_back(dp[newQx[i]][newQy[i]]);
    qx.swap(newQx);
    qy.swap(newQy);
    qv.swap(newQv);
  }
  int res = 0;
  FOR(i, 0, SIZE(qx)) {
    res = max(res, dp[qx[i]][qy[i]]);
  }
  return res;
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%s%s%d", s1, s2, &K);
    n = CAST<int>(strlen(s1));
    m = CAST<int>(strlen(s2));
    init(n, s1, jump1);
    init(m, s2, jump2);
    FOR(i, 0, n + 1) {
      memset(dp[i], 0xFF, sizeof(int) * (m + 1));
      memset(tag[i], 0xFF, sizeof(int) * (m + 1));
    }
    printf("%d\n", calc());
  }
  return 0;
}
