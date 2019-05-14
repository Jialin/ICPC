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

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

vector<int> slots;
vector<char> answer;
char token[5];
map<char, vector<int>> newSlots;
set<char> cs;

void calc(int idx) {
  int nxtSize = (SIZE(slots) + 1) / (5 - idx) - 1;
  newSlots.clear();
  for (char c : cs) newSlots[c].clear();
  for (int slot : slots) {
    printf("%d\n", slot * 5 + idx + 1);
    FLUSH;
    scanf("%s", token);
    newSlots[token[0]].push_back(slot);
  }
  for (auto& p : newSlots) if (SIZE(p.second) == nxtSize) {
    answer.push_back(p.first);
    cs.erase(cs.find(p.first));
    slots = p.second;
    return;
  }
  assert(false);
}

int main() {
  int taskNumber; scanf("%d%*d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    slots.resize(119); FOR(i, 0, 119) slots[i] = i;
    answer.clear();
    for (char c = 'A'; c <= 'E'; ++c) cs.insert(c);
    FOR(i, 0, 4) calc(i);
    answer.push_back(*cs.begin());
    FOR(i, 0, 5) putchar(answer[i]); putchar('\n');
    FLUSH;
    scanf("%s", token);
    assert(token[0] == 'Y');
  }
  return 0;
}
