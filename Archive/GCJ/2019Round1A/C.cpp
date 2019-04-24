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

int n;
char line[64];
set<string> ss;
map<string, vector<string>> sMap;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    ss.clear();
    FOR(i, 0, n) {
      scanf("%s", line);
      ss.insert(line);
    }
    int res = 0;
    for (int length = 50; length > 0; --length) {
      sMap.clear();
      for (auto& s : ss) if (SIZE(s) >= length) {
        string sub = s.substr(s.size() - length);
        sMap[sub].push_back(s);
      }
      for (auto& psv : sMap) if (psv.second.size() > 1) {
        auto& x = psv.second[0];
        auto& y = psv.second[1];
        ss.erase(x);
        ss.erase(y);
        res += 2;
      }
    }
    printf("Case #%d: %d\n", taskIdx, res);
  }
  return 0;
}
