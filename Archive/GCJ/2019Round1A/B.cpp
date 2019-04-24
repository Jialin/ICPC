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

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)

#define FOR(i,l,r) for(int i=(l);i<(r);++i)
#define FOREACH(i,v) for(typeof((v).begin()) i=(v).begin();i!=(v).end();++i)

const int MOD[7] = {16, 9, 5, 7, 11, 13, 17};

int n, m, rem[7];

int main() {
  int taskNumber; scanf("%d%d%d", &taskNumber, &n, &m);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    FOR(round, 0, 7) {
      FOR(i, 0, 18) printf("%d%c", MOD[round], i == 17 ? '\n' : ' ');
      fflush(stdout);
      int sum = 0;
      FOR(i, 0, 18) {
        int tmp; scanf("%d", &tmp);
        sum += tmp;
      }
      rem[round] = sum % MOD[round];
    }
    FOR(i, 1, m + 1) {
      bool res = true;
      FOR(round, 0, 7) if (i % MOD[round] != rem[round]) {
        res = false;
        break;
      }
      if (res) {
        printf("%d", i);
        fflush(stdout);
        break;
      }
    }
    int res; scanf("%d", &res);
    if (res == -1) break;
  }
  return 0;
}
