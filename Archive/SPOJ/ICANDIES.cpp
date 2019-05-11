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

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define SIZE(v) (static_cast<int>((v).size()))

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

const int MAXN = 1000000 + 1;

int answer[MAXN];

int main() {
  memset(answer, 0xFF, sizeof(answer));
  for (int i = 3, j = 8; j < MAXN; i += 3, j += 3) answer[j] = i;
  for (int i = 0, j = 5; j < MAXN; ++i, ++j) if (answer[i] >= 0) {
    answer[j] = max(answer[j], answer[i]);
  }
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    printf("Case %d: %d\n", taskIdx, answer[n]);
  }
  return 0;
}
